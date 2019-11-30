#!/usr/bin/env python
# -*- coding:UTF-8 -*-

import rospy
from msgfile.msg import VoiceOrder
import time

class VoiceIO:

    name = ''
    doneNames = dict()
    releaseTime = 10
    startFlag = False

    def __init__(self):
        self.startFlag = False

    def start(self):
        self.startFlag = True
        print('VoiceIO start...')
        return self.startFlag
    
    def stop(self):
        self.startFlag = False
        return self.startFlag

    def releaseName(self):
        if len(self.doneNames) > 0:
            self.doneNames = dict(
                filter(lambda x: time.time() - x[1] < self.releaseTime, self.doneNames.items()))

    def voiceback(self, data):
        if data.OrderFinish and self.name != '':
            print('\n', time.time(), ': ')
            print(' Complete_True: ' + rospy.get_caller_id() + '\n' + "I heard :", data.name)
            self.doneNames[self.name] = time.time()
            print(self.doneNames)
            self.releaseName()
        else :
            print('\n', time.time(), ': ')            
            print(' Complete_False: ' + rospy.get_caller_id() + '\n' + "I heard :", data.name)



def callback(data):
    global voiceIO
    if voiceIO.startFlag is True:
        voiceIO.voiceback(data)
    else:
        rospy.logwarn('\n\nvoiceIO in voice_Subscirber.py stoped.\n\n')

def listener():
    rospy.init_node('VoiceIO', anonymous=True)
    rospy.Subscriber("VoicePub", VoiceOrder, callback)
    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

voiceIO = VoiceIO()

try:
    listener()
except Exception as e:
    print("[Exception] VoiceIO :", e)

# voiceIO = VoiceIO()
# voiceIO.run()
