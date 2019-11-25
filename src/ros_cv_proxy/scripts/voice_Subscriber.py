#!/usr/bin/env python
# -*- coding:UTF-8 -*-

import rospy
from msgfile.msg import VoiceOrder
import time


class VoiceIO:

    name = ''
    doneNames = []
    releaseTime = 10

    def __init__(self):
        # self.run()
        pass

    def run(self):
        try:
            self.listener()
        except Exception as e:
            print("[Exception] VoiceIO run()", e)

    def releaseName(self):
        if len(self.doneNames):
            self.doneNames = list( \
                filter(lambda x: time.time() - x['ts'] < self.releaseTime, self.doneNames))

    def voiceback(self, data):
        rospy.loginfo(rospy.get_caller_id() + "I heard :")
        print(data)
        if data.OrderFinish and self.name != '':
            self.doneNames.append(dict(ts=time.time(), name=self.name))
            self.releaseName()

    def listener(self):

        rospy.init_node('Voicelistener', anonymous=True)

        rospy.Subscriber("VoicePub", VoiceOrder, self.voiceback)

        # spin() simply keeps python from exiting until this node is stopped
        rospy.spin()
