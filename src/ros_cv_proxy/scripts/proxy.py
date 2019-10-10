#!/usr/bin/env python
import rospy
from ros_cv_proxy.msg import FaceTarget
# from std_msgs.msg import String

from mqutil import RSMQueue
import time
import json


context = {
    'target': -1,
    'mode': 'init'
}


def talker():

    pub = rospy.Publisher('custom_chatter', FaceTarget, queue_size=10)
    rospy.init_node('custom_talker', anonymous=True)
    qface = RSMQueue('faceDetector', '127.0.0.1')
    qrect= RSMQueue('faceTarget', '127.0.0.1')

    def ros_talker(message):
        d = json.loads(message)
        global context

        if isinstance(d, list) and len(d) > 0:
            if context['mode'] == 'init':
                d.sort(key=lambda x: x['location'][0])
                context['target'] += 1  # leftmost
                if context['target'] >= len(d):
                    context['mode'] = 'serve'
                    target = 0
                print(1, target, context['mode'])
            else:
                target = 0
                print(2, target, context['mode'])

            msg = FaceTarget()
            # msg.header.stamp.nsecs = int(time.time()*1000)
            face = d[target]
            msg.header.stamp = Header(stamp=rospy.Time.now(), frame_id='proxy')
            msg.cmd = context['mode']
            msg.target.x = (face['location'][0] + face['location'][2])/2
            msg.target.y = (face['location'][1] + face['location'][3])/2
            msg.target.z = 0
            print(msg)
            if not rospy.is_shutdown():
                rospy.loginfo(msg)
                pub.publish(msg)
                qrect.publish(face['location'])
            return True

    t = qface.subscribe(ros_talker)
    t.join()


if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException: pass
