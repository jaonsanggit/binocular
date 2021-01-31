#!/usr/bin/env python
# -*- coding:UTF-8 -*-
import rospy
from msgfile.msg import FaceTarget
from msgfile.msg import VoiceOrder
from msgfile.msg import Core2Voice
from std_msgs.msg import String, Header
from collections import defaultdict

from sys import getsizeof

from mqutil import RSMQueue
from queue import Queue
import time
import threading
import json
from pprint import pprint

#talker main()

def talker():

    pub_eyes = rospy.Publisher('core_eyes', FaceTarget, queue_size=10)
    
    rospy.init_node('core', anonymous=True)

    qface = RSMQueue('faceDetector', '127.0.0.1')
    qrect= RSMQueue('faceTarget', '127.0.0.1')

    header_eyes = Header(seq=0, stamp=rospy.Time.now(), frame_id='core')
    
    def ros_talker(message):

        try:

            face_msg = json.loads(message)
            print(face_msg)

            header_eyes.stamp=rospy.Time.now()
            face = face_msg[0]

            eyesmsg = FaceTarget()
            eyesmsg.header = header_eyes
            eyesmsg.target.x = (face['location'][0] + face['location'][2])/2
            eyesmsg.target.y = (face['location'][1] + face['location'][3])/2
            eyesmsg.target.z = 400
           
            workinginfo = ('raw_proxy: depth first tracking')
            rospy.loginfo('\n\n------------------- %s -------------------', workinginfo)

            if not rospy.is_shutdown():
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
                qrect.publish(face)
            return True
        except Exception as e:
            print("[Exception] talk()", e)

    t = qface.subscribe(ros_talker, 100)
    t.join()


if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException as e: 
        print('[Exception] talker', e)
        pass
