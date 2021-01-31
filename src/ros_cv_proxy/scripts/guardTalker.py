#!/usr/bin/env python
# -*- coding:UTF-8 -*-

import rospy
import time
from mqutil import RSMQueue
from std_msgs.msg import String, Header
from msgfile.msg import FaceTarget
from guardface import FaceIO
from guardcard import CardIO

def cardIOAliveCheck(c):
    if time.time() - c.time > 5:
        return False
    return True

def getStatus(c,f):
    if cardIOAliveCheck(c) is True:
        return 'working'
    else:
        return 'idle'

def getTarget(c,f):
    if len(f.face) > 0:
        for ff in f.face:
            if ff['user_name'] == c.current_card.get('Pname', '-1'):
                return ff
        return f.face[0]
    return []

def mqPub(qrect,face):
    qrect.publish(face)


def talker():
    pub_eyes = rospy.Publisher('core_eyes', FaceTarget, queue_size=10)

    rospy.init_node('core', anonymous=True)

    header_eyes = Header(seq=0, stamp=rospy.Time.now(), frame_id='core')

    qrect = RSMQueue('faceTarget', '127.0.0.1')

    #start FaceIO
    faceIO = FaceIO()
    faceIO.run()
    lastTarget = FaceTarget(header=header_eyes,cmd = 'idle')
    lastTarget.target.x = 50
    lastTarget.target.y = 50
    lastTarget.target.z = 100

    # start CardIO
    cardIO = CardIO()
    cardIO.run()

    rate = rospy.Rate(20)
    while not rospy.is_shutdown():

    
        header_eyes.stamp = rospy.Time.now()
        eyesmsg = FaceTarget()
        eyesmsg.header = header_eyes
        eyesmsg.cmd = getStatus(cardIO,faceIO)
        eyesmsg.target = lastTarget.target

        face = getTarget(cardIO,faceIO)
        if len(face) > 0:
            eyesmsg.target.x = (face['location'][0] + face['location'][2])*100/2
            eyesmsg.target.y = (face['location'][1] + face['location'][3])*100/2
            eyesmsg.target.z = 100
            lastTarget.target = eyesmsg.target

            if getStatus(cardIO, faceIO) == 'working':

                workinginfo = 'depth first tracking'
                print('\n\n------------------- %s -------------------', workinginfo)
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
                mqPub(qrect,face)

        rate.sleep()


if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException as e:
        print('[Exception] talker', e)
        pass
