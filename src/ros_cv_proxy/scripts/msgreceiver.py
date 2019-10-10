#!/usr/bin/env python
# -*- coding: utf-8 -*-

__author__ = 'werewolfLu'

# !/usr/bin/env python
import rospy
from std_msgs.msg import String
# from ros_cv_proxy.msg import FaceTarget


def callback(data):
    rospy.loginfo(rospy.get_caller_id() + "I heard %s", str(data))


def listener():
    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.init_node('listener', anonymous=True)

    rospy.Subscriber("custom_chatter", String, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()


if __name__ == '__main__':
    listener()