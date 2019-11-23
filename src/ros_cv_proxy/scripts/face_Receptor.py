#!/usr/bin/env python
# -*- coding:UTF-8 -*-

from mqutil import RSMQueue
from collections import defaultdict
import json
import time

class FaceIO:

#------mqueue-------
  qface = RSMQueue('faceDetector', '127.0.0.1')
  qrect = RSMQueue('faceTarget', '127.0.0.1')
  mqInput = []
  
#------FSM context-------
  face_list = []
  face = []
  trackingFace = []

  mode = 'idle'
  time = time.time()
  face_list_len = 20
  face_list_timeval = 3

#------activating-------
  effective_face_distance = 4000
  activateDis = 3000
  activateTime = 1.5

#------init-------
  lookAroundTime = 0.5
  maxLookAroundNum = 3

#------working-------
  nameCount = defaultdict(int)

  def __init__(self):
    self.mqInput = self.qface.subscribe(self.run, 100)
    self.mqInput.join()

  def run(self, message):
    self.Getface(message)
    self.FSM()

  def Getface(self, message):
    face_msg = json.loads(message)
    self.face = self.face_distance_filter(face_msg, self.effective_face_distance)
    self.pushFace(self.face)

  def pushFace(self, face):
    if face is not None:
      self.face_list.append(dict(ts=time.time(), msg = face))
    
    self.face_list = list(filter(lambda x: time.time() - x['ts'] > self.face_list_timeval, self.face_list))

    if len(self.face_list) > self.face_list_len:
      self.face_list.pop(0)
 
  def face_distance_filter(self, face, distance):
    face = list(filter(lambda x: x['depth'] < distance, face))
    return face

  def nameCount(self):
    name_dict = defaultdict(int)
    for f in self.face_list:
        f = f['msg']
        f = list(filter(lambda x: x['user_name'] is not None, f))
        for ff in f:
            name_dict[ff['user_name']] += 1

    #sort by frequency      
    name_dict = sorted(name_dict.items(),key=lambda d : d[1],reverse=True) 
    
    self.nameCount = name_dict

  def setFSM(self, mode):
    self.mode = mode
    self.face.clear()
    self.face_list.clear()
    self.time = time.time()

  def FSM(self):
    if self.mode == 'idle':
      self.time = time.time()
      self.face = list(filter(lambda x: x['depth'] < self.activateDis, self.face))
      if len(self.face) == 0:
        self.setFSM('idle')
      else :
        self.setFSM('activating')
        print('idle -> activating')

    elif self.mode == 'activating':
      self.face = list(filter(lambda x: x['depth'] < self.activateDis, self.face))
      self.face_list[-1]['msg'] = self.face

      if time.time() - self.time < self.activateTime:
        print('激活时间: ', time.time() - self.time)
        face_list = list(filter(lambda x: x['msg'] is None , self.face_list))
        if len(face_list) / len(self.face_list) < 0.6:
          self.setFSM('idle')
          print('\t\t\t---激活失败，人脸出现率 %f----'%(len(face_list) / len(self.face_list)))
      else:
        self.setFSM('init')
        print('激活成功, 状态转移: idle -> init')
    elif self.mode == 'init':
        target = 0
        tval = time.time() - self.time
        for i in range(0,self.maxLookAroundNum):
          if tval > self.lookAroundTime*(i+1):
            break
          target += 1

          if target < len(self.face):
            self.face.sort(key=lambda x: x['location'][0], reverse=True)
            self.trackingFace = self.face[target]
            print('环顾中%d'%target)
          else:
            if len(self.nameCount) == 0:
              print('所有user_name都是none, 确定失败,重新确定 --> init')
              self.setFSM('init')
            else:
              self.nameCount()
              self.setFSM('working')
              print('状态转移: init -> working')
    #self.mode == working
    else :
      print('working frequency: ', \
        len(self.face_list) / (self.face_list[-1].get('ts') - self.face_list[-1].get('ts')), \
        ' Hz')