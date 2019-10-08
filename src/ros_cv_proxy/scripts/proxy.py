#!/usr/bin/env python
import rospy
from ros_cv_proxy.msg import FaceTarget
import time

def talker():
    pub = rospy.Publisher('custom_chatter', Num)
    rospy.init_node('custom_talker', anonymous=True)
    r = rospy.Rate(1) #10hz
    msg = Num()
    msg.header.stamp = time.time()
    msg.cmd = "run"
    msg.target.x = 20
    msg.target.y = 20
    msg.target.z = 0

    while not rospy.is_shutdown():
        rospy.loginfo(msg)
        pub.publish(msg)
        r.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException: pass
