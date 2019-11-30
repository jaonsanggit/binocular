#!/usr/bin/env python
# -*- coding:UTF-8 -*-

import rospy
from msgfile.msg import FaceTarget
from msgfile.msg import Core2Voice
from msgfile.msg import VoiceOrder
from std_msgs.msg import String, Header
import time

from ros_cv_proxy.scripts.face_Receptor import FaceIO
from ros_cv_proxy.scripts.voice_Subscriber import voiceIO

# from face_Receptor import FaceIO
# from voice_Subscriber import voiceIO

def faceIOAliveCheck(f):
    if time.time() - f.time > 3:
        return False
    return True

def faceIOWorkingCheck(f):
    if f.status == 'working' and time.time() - f.time > 1.3:
        return False
    return True


def FacemodeSwitch(f, mode='depth', v=None):
    # depth first Tracking
    f.excludeNames = []
    
    if mode != 'depth':
        if v is not None:
            f.excludeNames = list(v.doneNames.keys())
        else:
            print('voice is a INVALID handler')

def talker():
    pub_eyes = rospy.Publisher('core_eyes', FaceTarget, queue_size=10)
    pub_voice = rospy.Publisher('core_voice', Core2Voice, queue_size=10)

    rospy.init_node('core', anonymous=True)

    header_eyes = Header(seq=0, stamp=rospy.Time.now(), frame_id='core')
    header_voice = Header(seq=0, stamp=rospy.Time.now(), frame_id='core')


    #start FaceIO
    faceIO = FaceIO()
    faceIO.run()
    faceMode = 'depth'
    lastFaceTime = faceIO.time

    # start VoiceIO
    voiceIO.start()

    rate = rospy.Rate(50)
    while not rospy.is_shutdown():

        FacemodeSwitch(faceIO, faceMode)
        if not faceIOAliveCheck(faceIO):
            faceIO.setFSM('idle')
            print('dead')
        if not faceIOWorkingCheck(faceIO):
            rospy.logwarn('rosTalker: faceIOWorkingCheck Fail, set FaceIO: init')
            faceIO.setFSM('init')

        header_eyes.stamp = rospy.Time.now()
        header_voice.stamp = header_eyes.stamp

        face = faceIO.trackingFace
        # print('11111111')
        if len(face) == 0:
            # print('all face have done')
            continue

        status = faceIO.status
        eyesmsg = FaceTarget()
        eyesmsg.header = header_eyes
        eyesmsg.cmd = status
        eyesmsg.target.x = (face['location'][0] + face['location'][2])/2
        eyesmsg.target.y = (face['location'][1] + face['location'][3])/2
        eyesmsg.target.z = 200 if status == 'init' else 400

        # voiceIO.name = face['user_name'] if face['user_name'] is not None else ""
        # voiceIO.name = 'jason'
        # print(voiceIO.name, '11111111111111')
        voicemsg = Core2Voice()
        voicemsg.header = header_voice
        voicemsg.cmd = status
        voicemsg.name = face['user_name'] if face['user_name'] is not None else ""
        voicemsg.gender = face['gender'] if face['gender'] is not None else ""
        # print('age: ', face['age'])
        # voicemsg.age = face['age'] if face['age'] is not None else 0
        voicemsg.age = 0

        if lastFaceTime < faceIO.time:

            workinginfo = ('name first tracking' if faceMode !=
                        'depth' else 'depth first tracking')
            rospy.loginfo(
                '\n\n------------------- %s -------------------', workinginfo)
            print('frame_id: ', eyesmsg.header.frame_id)
            print('seq: ', eyesmsg.header.seq)
            print('cmd: ', eyesmsg.cmd)

            print()
            print('  ----------eyesmsg----------')
            print('  core2eyes/FaceTarget')
            print('    target: ')
            print('    x: ', eyesmsg.target.x)
            print('    y: ', eyesmsg.target.y)
            print('    z: ', eyesmsg.target.z)

            print()
            print('  ----------voicemsg----------')
            print('  core2voice/Core2Voice')
            print('    name: ', voicemsg.name)
            print('    gender: ', voicemsg.gender)
            print('    age: ', voicemsg.age)
            print('\n\n')

            pub_eyes.publish(eyesmsg)
            # print('1111111111111')
            pub_voice.publish(voicemsg)
            # print('2222222222')
            lastFaceTime = faceIO.time

        rate.sleep()


if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException as e:
        print('[Exception] talker', e)
        pass
