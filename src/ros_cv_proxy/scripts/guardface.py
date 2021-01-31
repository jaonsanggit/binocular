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
    mqInput = []

# ------FSM context-------
    face_list = []
    face = []
    trackingFace = []
    
    status = 'idle'
    time = time.time()
    face_list_len = 10
    face_list_timeval = 2

# ------activating-------
    effective_face_distance = 1500


    def __init__(self):
        print('FaceIO start....')

    def run(self):

        def callback(message, obj):
            try:
                obj.Getface(message)
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
        # print(face_msg)
        self.face = self.face_distance_filter(
            face_msg, self.effective_face_distance)
        self.pushFace(self.face)

    def pushFace(self, face):
        if len(face) > 0 :
            self.face_list.append(dict(ts=time.time(), msg=face))

        self.face_list = list(filter(lambda x: time.time(
        ) - x['ts'] < self.face_list_timeval, self.face_list))

        if len(self.face_list) > self.face_list_len:
            self.face_list.pop(0)

    def face_distance_filter(self, face, distance):
        face = list(filter(lambda x: x['depth'] < distance, face))
        return face




