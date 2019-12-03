#!/usr/bin/env python
# -*- coding:UTF-8 -*-

import rospy
from msgfile.msg import VoiceOrder
import time


class VoiceIO:

    name = ''
    # dict{name: finishTime}
    doneNames = dict()
    releaseTime = 10
    startFlag = False
    finish = False

    def __init__(self):
        self.startFlag = True

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
        self.releaseName()
        if data.OrderFinish is True:
            print('\n', time.time(), ': ')
            print(' Complete_True: ' + rospy.get_caller_id() +
                  '\n' + "I heard :", data.name)
            self.finish = True
            if self.name is not None and self.name != '':
                self.doneNames[self.name] = time.time()

            print(self.doneNames)
        else:
            self.finish = False
            print('\n', time.time(), ': ')
            print(' Complete_False: ' + rospy.get_caller_id() +
                  '\n' + "I heard :", data.name)

    def run(self):
        def callback(data, obj):
            if obj.startFlag is True:
                obj.voiceback(data)
            else:
                rospy.logwarn('\n\nvoiceIO in voice_Subscirber.py stoped.\n\n')

        rospy.Subscriber("VoicePub", VoiceOrder, callback, (self))


# def callback(data):
#     global voiceIO
#     if voiceIO.startFlag is True:
#         voiceIO.voiceback(data)
#     else:
#         rospy.logwarn('\n\nvoiceIO in voice_Subscirber.py stoped.\n\n')

# def listener():
#     # rospy.init_node('VoiceIO', anonymous=True)
#     rospy.Subscriber("VoicePub", VoiceOrder, callback)
#     # spin() simply keeps python from exiting until this node is stopped
#     # rospy.spin()

# voiceIO = VoiceIO()

# if __name__ == "__main__":
#     try:
#         listener()
#     except Exception as e:
#         print("[Exception] VoiceIO :", e)

# voiceIO = VoiceIO()
# voiceIO.run()
