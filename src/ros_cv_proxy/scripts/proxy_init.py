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

context = {
    'target': -1,
    'mode': 'idle',
    'ts': time.time()
}
face_msg_list = []


def fun_timer():
    print('Hello Timer!')
    global timer
    global context
    global pub

    if time.time() - context['ts'] < 3: return

    context.update({
        'target': -1,
        'mode': 'idle',
        'ts': time.time(),
    })

    print('=============>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Hello Timer!')

    msg = FaceTarget()
    msg.cmd = context['mode']
    if not rospy.is_shutdown():
        rospy.loginfo(msg)
        pub.publish(msg)

def Status_Machine():
    
    global context
    global face_msg
    global timer
    global face_msg_list

# 超过3s没有消息 置为 idle
    try:
        timer.cancel()
    except Exception as e:
        pass
    timer = threading.Timer(3, fun_timer)
    timer.start()

    context['ts'] = time.time()
    
    mode = context['mode']

    if mode == 'idle':
        if (face_msg_list[-1].get('ts') - face_msg_list[0].get('ts')) < 1:
            context['target'] = -1
            context['mode'] = 'idle'
            print('激活时间: ', face_msg_list[-1].get('ts') - face_msg_list[0].get('ts'))
        else:
            context['mode'] = 'init'
            context['target'] = 0
            print('状态转移: idle -> init')
    elif mode == 'init' :
        if context['target'] < 1:
            context['mode'] = 'init'
            context['target'] += 0.1
        else : 
            context['mode'] = 'working'
            context['target'] = 0
            print('状态转移: idle -> init')
    else :
        context['mode'] = 'working'
        context['target'] = 0        

    #Status_Machine Handler
    mode = context['mode']
    if mode == 'idle':
        return
    elif mode == 'init':
        print('init ----------> target: ', context['target'])
    else:    #   working
        face_msg.sort(key=lambda x: x['depth'])
        context['target'] = 0

    return face_msg[max(0, int(context['target']))]


def talker():

    pub = rospy.Publisher('core_eyes', FaceTarget, queue_size=10)
    
    rospy.init_node('core', anonymous=True)

    qface = RSMQueue('faceDetector', '127.0.0.1')
    qrect= RSMQueue('faceTarget', '127.0.0.1')

    header = Header(seq=0, stamp=rospy.Time.now(), frame_id='core')
    
    def ros_talker(message):

        global context
        global face_msg
        global face_msg_list

        face_msg = json.loads(message)

        face_msg = list(filter(lambda x: x['depth'] < 4000, face_msg))
        if len(face_msg) == 0:
            print('所有人4000以外')
            return


        face_msg_list.append(dict(ts=time.time(), msg=face_msg))

        if len(face_msg_list) > 20:
            face_msg_list.pop(0)

        face = Status_Machine()
        # print(face)

        header.stamp=rospy.Time.now()

        eyesmsg = FaceTarget()
        eyesmsg.header = header
        eyesmsg.cmd = context['mode']

        eyesmsg.target.x = (face['location'][0] + face['location'][2])/2
        eyesmsg.target.y = (face['location'][1] + face['location'][3])/2
        eyesmsg.target.z = 400

        if context['mode'] == 'init' :
            eyesmsg.target.x = 960
            eyesmsg.target.y = 540
            eyesmsg.target.z = 200

        workinginfo = ('init_proxy: depth first tracking')
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
            print('\n\n')

            pub.publish(eyesmsg)
            qrect.publish(face)
        return True

    t = qface.subscribe(ros_talker, 100)
    t.join()


if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException as e: 
        print('[Exception] talker', e)
        pass
