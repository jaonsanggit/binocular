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
    
    status = 'working'
    time = time.time()
    face_list_len = 20
    face_list_timeval = 3

# ------activating-------
    effective_face_distance = 1000
    activateDis = 700
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

        self.namebyFrequency = list(filter(lambda d: d[1] > 0, name_dict))

    def mqPub(self):
        self.qrect.publish(self.face[0])

    def faceCheck(self):

        for f in self.face:
            if f['user_name'] is None:
                # f['user_name'] = 'unknown_d'
                f['user_name'] = 'unknown'

        if len(self.face) == 0 or len(self.face_list) == 0:
            print('ignore frame')
            return False

        #if self.face[0]['user_name'] is None:
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

    def printlog(self):
        print(self.face)

    def FSM(self):

        self.time = time.time()
        self.trackingFace = self.face[0]
        self.trackingName = self.trackingFace['user_name']
        # print('trackingFace: ', self.trackingFace)
        #print('trackingName: ', self.trackingName)
