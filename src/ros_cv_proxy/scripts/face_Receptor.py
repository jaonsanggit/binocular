#!/usr/bin/env python
# -*- coding:UTF-8 -*-

from mqutil import RSMQueue
from collections import defaultdict
import json
import time
import threading

class FaceIO():

    # ------mqueue-------
    qface = RSMQueue('faceDetector', '127.0.0.1')
    qrect = RSMQueue('faceTarget', '127.0.0.1')
    mqInput = []

# ------FSM context-------
    face_list = []
    face = []
    trackingFace = []
    
    status = 'idle'
    time = time.time()
    face_list_len = 20
    face_list_timeval = 3

# ------activating-------
    effective_face_distance = 4000
    activateDis = 3000
    activateTime = 1.5

# ------init-------
    lookAroundTime = 1
    maxLookAroundNum = 3

# ------working-------
    namebyFrequency = []
    #dict{name: LastAppearTime=time.time()}
    excludeNames = {}
    trackingName = ''

    def __init__(self):
        print('FaceIO start....')

    def run(self):

        def callback(message, obj):
            try:
                obj.Getface(message)
                obj.FSM()
                obj.mqPub()
                return True
            except Exception as e:
                print("[Exception] faceIO callback()", e)
        try:
            self.mqInput = self.qface.subscribe(callback, self, 100)
            return True
        except Exception as e:
            print("[Exception] faceIO run()", e)

    def Getface(self, message):
        face_msg = json.loads(message)
        self.face = self.face_distance_filter(
            face_msg, self.effective_face_distance)
        self.pushFace(self.face)

    def pushFace(self, face):
        if len(face) > 0 :
            self.face_list.append(dict(ts=time.time(), msg=face))

        # self.face_list = list(filter(lambda x: time.time(
        # ) - x['ts'] < self.face_list_timeval, self.face_list))

        if len(self.face_list) > self.face_list_len:
            self.face_list.pop(0)

    def face_distance_filter(self, face, distance):
        face = list(filter(lambda x: x['depth'] < distance, face))
        return face

    def leaveNamesCount(self):
        names = []
        for f in self.face:
            names.append(f['user_name'])
        
        #update excludeNames last appear time
        for l in self.excludeNames.keys():
            if names.count(l) > 0:
                self.excludeNames[l] = time.time()

    def nameCount(self):
        name_dict = defaultdict(int)
        for f in self.face_list:
            f = f['msg']
            if len(f) == 0:
                continue
            # f = list(filter(lambda x: x['user_name'] is not None, f))
            for ff in f:
                name_dict[ff['user_name']] += 1

        # sort by frequency
        name_dict = sorted(name_dict.items(), key=lambda d: d[1], reverse=True)

        self.namebyFrequency = name_dict

    def mqPub(self):
        if len(self.trackingFace) > 0 :
            self.qrect.publish(self.trackingFace)
        else:
            print("mqPub: trackingFace is None")

    def faceCheck(self):

        for f in self.face:
            if f['user_name'] is None:
                # f['user_name'] = 'unknown_d'
                f['user_name'] = 'unknown'

        if len(self.face) == 0 or len(self.face_list) == 0:
            print('ignore frame')
            return False

        # if self.face[0]['user_name'] is None:
        #     self.time = time.time()
        #     self.trackingFace = self.face[0]
        #     self.status = 'working'
        #     print('user_name is none, depth only')
        #     return False

        return True


    def setFSM(self, status):
        self.status = status
        self.face.clear()
        self.trackingFace.clear()
        self.face_list.clear()
        self.time = time.time()

    def FSM(self):

        # print(self.face)

        if self.faceCheck() is False:
            return

        self.leaveNamesCount()

        if self.status == 'idle':
            self.time = time.time()
            self.face = list(
                filter(lambda x: x['depth'] < self.activateDis, self.face))
            if len(self.face) == 0:
                self.setFSM('idle')
            else:
                self.setFSM('activating')
                print('idle -> activating')

        elif self.status == 'activating':

            self.face = list(
                filter(lambda x: x['depth'] < self.activateDis, self.face))
            self.face_list[-1]['msg'] = self.face

            if len(self.face) == 0:
                print('faces depth less than ', self.activateDis)
                # return
            
            if time.time() - self.time < self.activateTime:
                print('激活时间: ', time.time() - self.time)
                face_list = list(
                    filter(lambda x: len(x['msg']) > 0 , self.face_list))
                print(len(face_list), len(self.face_list))
                if len(face_list) / len(self.face_list) < 0.6:
                    self.setFSM('idle')
                    print('\t\t\t---激活失败，人脸出现率 %f----' %
                          (len(face_list) / len(self.face_list)))
            else:
                self.setFSM('init')
                print('激活成功, 状态转移: idle -> init')
        elif self.status == 'init':
            target = 0
            tval = time.time() - self.time
            for i in range(0, self.maxLookAroundNum):
                if tval < self.lookAroundTime*(i+1):
                    break
                target += 1

            # print('init:', len(self.face))
            if target < len(self.face):
                self.face.sort(
                    key=lambda x: x['location'][0], reverse=True)
                self.trackingFace = self.face[target]
                print('环顾中%d' % target)
            else:
                self.nameCount()
                if len(self.namebyFrequency) == 0:
                    print('所有user_name都是none, 确定失败,重新确定 --> init')
                    self.setFSM('init')
                else:
                    self.trackingName = ''

                    for n in self.namebyFrequency:
                        if n[0] is None or n[0] == 'unknown':
                            self.trackingName = n[0]
                            continue
                        elif list(self.excludeNames.keys()).count(n[0]) != 0:
                            self.trackingName = n[0]
                            continue
                        else :
                            self.trackingName = n[0]
                            break

                    if (list(self.excludeNames.keys()).count(self.trackingName) != 0):
                        print('\n\n------ Init : all tracked -------\n\n')
                        self.setFSM('init')
                    else :
                        self.setFSM('working')
                        print('状态转移: init -> working')
        #self.status == working
        else:
            target = 0
            if self.trackingName != 'unknown':
                for f in self.face:
                    if f['user_name'] == self.trackingName:
                        break
                    target += 1

                if target >= len(self.face):
                    self.trackingFace = []
                    print('Fail to track on: ', self.trackingName)
                    return
            else :
                target_candidate = []
                for i in range(0, len(self.face)):
                    if self.face[i]['depth'] - self.face[0]['depth'] > 100:
                        break
                    target_candidate.append(i)
                min_dr = 1000
                for t in target_candidate:
                    dr = abs(sum(self.face[t]['location']) - sum(self.trackingFace['location']))
                    if dr < min_dr:
                        min_dr = dr
                        target = t
                    
            self.time = time.time()
            self.trackingFace = self.face[target]
            # print('trackingFace: ', self.trackingFace)
            print('trackingName: ', self.trackingName)