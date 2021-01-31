#!/usr/bin/env python
# -*- coding:UTF-8 -*-

import rospy
from msgfile.msg import FaceTarget

from std_msgs.msg import String, Header
import time

#from ros_cv_proxy.scripts.face_Receptor import FaceIO
#from ros_cv_proxy.scripts.voice_Subscriber import VoiceIO

from face_Receptor2 import FaceIO

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

def Check(f):
    if not faceIOAliveCheck(f):
        f.setFSM('idle')
        rospy.logwarn('\n\nrosTalker: faceIOAliveCheck Fail, set FaceIO: idle')
        return False

    elif not faceIOWorkingCheck(f):
        rospy.logwarn('\n\nrosTalker: faceIOWorkingCheck Fail, set FaceIO: init')
        f.setFSM('init')
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
    pub_eyes = rospy.Publisher('core_eyes', FaceTarget, queue_size=1)

    rospy.init_node('core', anonymous=True)

    header_eyes = Header(seq=0, stamp=rospy.Time.now(), frame_id='core')

    #start FaceIO
    faceIO = FaceIO()
    faceIO.run()
    faceMode = 'name'
    lastFaceTime = faceIO.time
    lastTarget = FaceTarget(header=header_eyes,cmd = faceIO.status)
    lastTarget.target.x = 50
    lastTarget.target.y = 50
    lastTarget.target.z = 200
    # FacemodeSwitch(faceIO, faceMode)

    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
    
        header_eyes.stamp = rospy.Time.now()

        status = faceIO.status
        eyesmsg = FaceTarget()
        eyesmsg.header = header_eyes
        eyesmsg.cmd = status
        eyesmsg.target = lastTarget.target

        face = faceIO.trackingFace
        if len(face) > 0:
            eyesmsg.target.x = (face['location'][0] + face['location'][2])*100/2
            eyesmsg.target.y = (face['location'][1] + face['location'][3])*100/2
            eyesmsg.target.z = speedControl(faceIO)
            lastTarget.target = eyesmsg.target

    #       if lastFaceTime < faceIO.time:

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

            pub_eyes.publish(eyesmsg)
    #            lastFaceTime = faceIO.time

        rate.sleep()


if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException as e:
        print('[Exception] talker', e)
        pass
