#!/usr/bin/env python
# -*- coding:UTF-8 -*-

import rospy
from msgfile.msg import FaceTarget
from msgfile.msg import VoiceOrder
from msgfile.msg import Core2Voice
from std_msgs.msg import String, Header
from collections import defaultdict
import time

from ros_cv_proxy.scripts.face_Receptor import FaceIO
from ros_cv_proxy.scripts.voice_Subscriber import VoiceIO

# talker main()

def faceIOCheck(f):
  if time.time() - f.time > 3:
    return False
  return True

def FacemodeSwitch(f, mode='depth', v=None):
#depth first Tracking  
  if mode == 'depth':
    f.excludeName = []
  else:
    if v is not None:
      f.excludeName = v.doneName
    else :
      print('voice is a INVALID handler')


def talker():

  pub_eyes = rospy.Publisher('core_eyes', FaceTarget, queue_size=10)
  pub_voice = rospy.Publisher('core_voice', Core2Voice, queue_size=10)

  rospy.init_node('core', anonymous=True)

  rate = rospy.Rate(50)

  header_eyes = Header(seq=0, stamp=rospy.Time.now(), frame_id='core')
  header_voice = Header(seq=0, stamp=rospy.Time.now(), frame_id='core')

  faceIO = FaceIO()
  faceMode = 'depth'

  voiceIO = VoiceIO()

  while not rospy.is_shutdown():
    
    FacemodeSwitch(faceIO, faceMode)
    if faceIO.trackingFace is None:
      print('all face have done')
      continue

    header_eyes.stamp=rospy.Time.now()
    header_voice.stamp=header_eyes.stamp

    face = faceIO.trackingFace
    status = faceIO.status
    eyesmsg = FaceTarget()
    eyesmsg.header = header_eyes
    eyesmsg.cmd = faceIO.mode
    eyesmsg.target.x = (face['location'][0] + face['location'][2])/2
    eyesmsg.target.y = (face['location'][1] + face['location'][3])/2
    eyesmsg.target.z = 200 if status == 'init'  else 400

    voiceIO.name = face['user_name']
    voicemsg = Core2Voice()
    voicemsg.header = header_voice
    voicemsg.cmd = status
    voicemsg.name = face['user_name']
    voicemsg.gender = face['gender'] if face['gender'] is not None else ""
    voicemsg.age = face['age'] if face['age'] is not None else 0

    workinginfo = ('name first tracking' if faceMode != 'depth' else  'depth first tracking')
    rospy.loginfo('\n\n------------------- %s -------------------', workinginfo)
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

    rate.sleep()

  if __name__ == '__main__':
    try:
      talker()
    except rospy.ROSInterruptException as e:
      print('[Exception] talker', e)
      pass
