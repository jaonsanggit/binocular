#!/usr/bin/env python
# -*- coding:UTF-8 -*-

import rospy
from msgfile.msg import FaceTarget
from msgfile.msg import Core2Voice
from msgfile.msg import VoiceOrder

from std_msgs.msg import String, Header
import time

#from ros_cv_proxy.scripts.face_Receptor import FaceIO
#from ros_cv_proxy.scripts.voice_Subscriber import VoiceIO

from face_Receptor import FaceIO
from voice_Subscriber import VoiceIO

def faceIOAliveCheck(f):
    if time.time() - f.time > 3:
        return False
    return True

def faceIOWorkingCheck(f):
    if f.status == 'working' and time.time() - f.time > 2:
        return False
    return True


def FacemodeSwitch(f, mode='depth'):

    if mode == 'depth':
        f.excludeNames = []
    # depth first Tracking
    # f.excludeNames = []
    # if mode != 'depth':
    #     if v is not None:
    #         if f.excludeNames != list(v.doneNames.keys()):
    #             f.excludeNames = list(v.doneNames.keys())
    #     else:
    #         print('voice is a INVALID handler')

def VoiceFinishCheck(f, v):

#update f.excludeNames key:name
    d_e = list(set(v.doneNames.keys()).difference(set(f.excludeNames.keys())))
    e_d = list(set(f.excludeNames.keys()).difference(set(v.doneNames.keys())))
    for d in d_e:
        f.excludeNames[d] = v.doneNames[d]
    for e in e_d:
        f.excludeNames.pop(e)

#update v.doneNames value :last appear time
    for e in f.excludeNames.keys():
        v.doneNames[e] = f.excludeNames[e]
        
    v.releaseName()
    # print('\n\n\n', v.doneNames, '\n\n\n')

    if v.finish is True:
        v.finish = False
        return True
    return False

def Check(f, v):
    if not faceIOAliveCheck(f):
        f.setFSM('idle')
        v.name = ''
        rospy.logwarn('\n\nrosTalker: faceIOAliveCheck Fail, set FaceIO: idle')
        return False

    elif not faceIOWorkingCheck(f):
        rospy.logwarn('\n\nrosTalker: faceIOWorkingCheck Fail, set FaceIO: init')
        f.setFSM('init')
        v.name = ''
        return False        

    elif VoiceFinishCheck(f, v):
        rospy.logwarn('rosTalker: VoiceIOFinishCheck True, set FaceIO: init')
        rospy.logwarn('\n\n\t\t---------%s finish-----------', v.name)
        f.setFSM('init')
        v.name = ''
        return False
    else:
        return True

def speedControl(f):
    speed = 100
    if f.status == 'working' :
        speed = 400
        if f.trackingName == 'unknown':
            speed = 200
    else :
        speed = 200
    return speed

def talker():
    pub_eyes = rospy.Publisher('core_eyes', FaceTarget, queue_size=10)
    pub_voice = rospy.Publisher('core_voice', Core2Voice, queue_size=10)

    rospy.init_node('core', anonymous=True)

    header_eyes = Header(seq=0, stamp=rospy.Time.now(), frame_id='core')
    header_voice = Header(seq=0, stamp=rospy.Time.now(), frame_id='core')


    #start FaceIO
    faceIO = FaceIO()
    faceIO.run()
    faceMode = 'name'
    lastFaceTime = faceIO.time
    lastTarget = FaceTarget(header=header_eyes,cmd = faceIO.status)
    lastTarget.target.x = 50
    lastTarget.target.y = 50
    lastTarget.target.z = 100
    # FacemodeSwitch(faceIO, faceMode)

    # start VoiceIO
    voiceIO = VoiceIO()
    voiceIO.run()

    rate = rospy.Rate(50)
    while not rospy.is_shutdown():

        Check(faceIO, voiceIO)
    
        header_eyes.stamp = rospy.Time.now()
        header_voice.stamp = header_eyes.stamp

        status = faceIO.status
        eyesmsg = FaceTarget()
        eyesmsg.header = header_eyes
        eyesmsg.cmd = status if status != 'activating' else 'idle'
        eyesmsg.target = lastTarget.target

        voiceIO.name = faceIO.trackingName
        voicemsg = Core2Voice()
        voicemsg.header = header_voice
        voicemsg.cmd = status

        face = faceIO.trackingFace
        if len(face) > 0:
            eyesmsg.target.x = (face['location'][0] + face['location'][2])*100/2
            eyesmsg.target.y = (face['location'][1] + face['location'][3])*100/2
            eyesmsg.target.z = speedControl(faceIO)
            lastTarget.target = eyesmsg.target

            voicemsg.name = faceIO.trackingName
            voicemsg.gender = face['gender'] if face['gender'] is not None else ""
        # print('age: ', face['age'])
            if voicemsg.gender != '':
                if voicemsg.gender == 'female':
                    voicemsg.age = 18
                else:
                    voicemsg.age = face['age'] if face['age'] is not None else 0

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
