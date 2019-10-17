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

    'user_name': '',
    'ts': time.time(),
    'name_timer': time.time()
}
face_msg_list = []
name_list = []
OrderFinish = False
timer = None
pub_eyes = None
pub_voice = None

def fun_timer():
    global timer
    global pub_eyes
    global context
    global face_msg_list

    if time.time() - context['ts'] < 3: 
        return

    print('=============>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Hello Timer!')

    context.update({
        'target': -1,
        'mode': 'idle',
        'user_name': '',
        'ts': time.time(),
        'name_timer': time.time()
    })

    
    face_msg_list = []

    msg = FaceTarget()
    msg.cmd = context['mode']
    if not rospy.is_shutdown():
        rospy.loginfo(msg)
        pub_eyes.publish(msg)
    
    timer = threading.Timer(3, fun_timer)
    timer.start()

def Status_Machine(face_msg):
    
    global context
    global timer
    global face_msg_list
    global OrderFinish
    global name_list

# 超过3s没有消息 置为 idle
    try:
        timer.cancel()
    except Exception as e:
        pass
    timer = threading.Timer(3, fun_timer)
    timer.start()

    context['ts'] = time.time()

    #更新服务过的name
    name_list = list(filter(lambda x: x['ts'] - time.time() < 10, name_list))

#滤除4000以外的目标
    # print(face_msg)
    face_msg = list(filter(lambda x: x['depth'] < 4000, face_msg))
    if len(face_msg) == 0:
        print('所有人4000以外')
        return
 
    face_msg_list.append(dict(ts=time.time(), msg=face_msg))
    if len(face_msg_list) > 20:
        face_msg_list.pop(0)

    # print('\n\nface_msg_list ', len(face_msg_list))
    # print('face_msg ', len(face_msg))

    mode = context['mode']
#语音端识别到完成
    if OrderFinish:
        context['target'] = 0
        context['mode'] = 'init'
        OrderFinish = False
    elif mode == 'idle':
#激活距离
        print('depth ', face_msg[0]['depth'])
        face_msg = list(filter(lambda x: x['depth'] < 3000, face_msg))
        if len(face_msg) == 0:
            context['target'] = -1
            context['mode'] = 'idle'
            face_msg_list.pop(-1)
 #激活时间
        elif (face_msg_list[-1].get('ts') - face_msg_list[0].get('ts')) < 1.5:
            context['target'] = -1
            context['mode'] = 'idle'
            print('激活时间: ', face_msg_list[-1].get('ts') - face_msg_list[0].get('ts'))
        # elif context['target'] == -1:
        else:
            context['mode'] = 'init'
            context['target'] = 0
            print('状态转移: idle -> init')
#环顾
    elif mode == 'init':
        if context['target'] < len(face_msg):
            context['user_name'] = ''
            context['mode'] = 'init'
            context['target'] += 0.1
            print('环顾')
#确定True user_name
        else: 
            name_dict = defaultdict(int)
            for f in face_msg_list:
                f = f['msg']
                f = list(filter(lambda x: x['user_name'] is not None, f))
                for ff in f:
                    name_dict[ff['user_name']] += 1
    #确定失败,重新确定        
            if len(name_dict.keys()) == 0:
                context['target'] = 0
                context['mode'] = 'init'
                return

            name_dict = sorted(name_dict.items(),key=lambda d : d[1],reverse=True) 
            print(11111111, name_dict)
            
            done_names = []
            for n in name_list:
                done_names.append(n['name'])

        #如果有没服务过的 选择, 如果都服务过 执行 depth first tracking
            for n in name_dict:
                if done_names.count(n[0]) != 0:
                    name = "unknown"
                else :
                    name = n[0]
                    break

            # name = name_dict[0][0]

            if (name == "unknown"):
                context['user_name'] = ''
            else :
                # name_list.append(dict(ts=time.time(), name=name))
                context['user_name'] = name

            context['mode'] = 'working'
            # context['target'] = 0
            print('状态转移: init -> working')
#正常跟随最近的face
    else :
        context['mode'] = 'working'       
        # context['target'] = 0
        # print(context['user_name'])

#Status_Machine Handler
    mode = context['mode']
    name = context['user_name']
#idle
    if mode == 'idle':
        return
#init
    elif mode == 'init':
        face_msg.sort(key=lambda x: x['location'][0], reverse=True)
        target = context['target']
#working
    else: 
        target = 0
        face_msg.sort(key=lambda x: x['depth'])
    #depth first tracking
        if name == "":
            target = 0
    #name first tracking    
        else :
            # name_timer = time.time()
            for f in face_msg:
                if f['user_name'] == name:
                    context["name_timer"] = time.time()
                    break
                target += 1

            if target == len(face_msg):
                if time.time() - context["name_timer"] > 1:
                    context['target'] = 0
                    context['mode'] = 'init'
                    print(context['name'], "lost for 1s, init start")
                    return


    target = min(max(0, int(target)), len(face_msg)-1)
    return face_msg[target]


#VoiceOrder Callback
def callback(data):
    global OrderFinish
    global name_list

    rospy.loginfo(rospy.get_caller_id() + "I heard: ")
    print(data)
    if data.OrderFinish :
        if context['user_name'] != '':
            name_list.append(dict(ts=time.time(), name=context['user_name']))
        OrderFinish = True
        

#talker main()
def talker():

    global pub_eyes
    pub_eyes = rospy.Publisher('core_eyes', FaceTarget, queue_size=10)
    pub_voice = rospy.Publisher('core_voice', Core2Voice, queue_size=10)
    
    rospy.init_node('core', anonymous=True)

    rospy.Subscriber("VoicePub", VoiceOrder, callback)

    qface = RSMQueue('faceDetector', '192.168.31.184')
    qrect= RSMQueue('faceTarget', '192.168.31.184')

    header_eyes = Header(seq=0, stamp=rospy.Time.now(), frame_id='core')
    # header_voice = Header(seq=0, stamp=rospy.Time.now(), frame_id='core')
    
    def ros_talker(message):

        global context

        try:

            face_msg = json.loads(message)

            face = Status_Machine(face_msg)
            if face is None: return

            header_eyes.stamp=rospy.Time.now()

            eyesmsg = FaceTarget()
            eyesmsg.header = header_eyes
            eyesmsg.cmd = context['mode']
            eyesmsg.target.x = (face['location'][0] + face['location'][2])/2
            eyesmsg.target.y = (face['location'][1] + face['location'][3])/2
            eyesmsg.target.z = 200 if context['mode'] == 'init'  else 400

            voicemsg = Core2Voice()
            voicemsg.header = header_eyes
            voicemsg.cmd = context['mode']
            voicemsg.name = context['user_name']
            voicemsg.gender = face['gender'] if face['gender'] is not None else ""
            voicemsg.age = face['age'] if face['age'] is not None else 0
            # print('age: ', type(face['age']))
            
            workinginfo = 'name first tracking' if context['user_name'] != '' else  'depth first tracking'
            rospy.loginfo('\n\n------------------- %s -------------------', workinginfo if context['user_name'] != '' else context['mode'])
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
                
                print()
                print('  ----------voicemsg----------')
                print('  core2voice/Core2Voice')
                print('    name: ', voicemsg.name)
                print('    gender: ', voicemsg.gender)
                print('    age: ', voicemsg.age)
                print('\n\n')
                pub_eyes.publish(eyesmsg)
                pub_voice.publish(voicemsg)
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
