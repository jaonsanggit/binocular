;; Auto-generated. Do not edit!


(when (boundp 'msgfile::FaceTarget)
  (if (not (find-package "MSGFILE"))
    (make-package "MSGFILE"))
  (shadow 'FaceTarget (find-package "MSGFILE")))
(unless (find-package "MSGFILE::FACETARGET")
  (make-package "MSGFILE::FACETARGET"))

(in-package "ROS")
;;//! \htmlinclude FaceTarget.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass msgfile::FaceTarget
  :super ros::object
  :slots (_header _cmd _target _name ))

(defmethod msgfile::FaceTarget
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:cmd __cmd) "")
    ((:target __target) (instance geometry_msgs::Point :init))
    ((:name __name) "")
    )
   (send-super :init)
   (setq _header __header)
   (setq _cmd (string __cmd))
   (setq _target __target)
   (setq _name (string __name))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:cmd
   (&optional __cmd)
   (if __cmd (setq _cmd __cmd)) _cmd)
  (:target
   (&rest __target)
   (if (keywordp (car __target))
       (send* _target __target)
     (progn
       (if __target (setq _target (car __target)))
       _target)))
  (:name
   (&optional __name)
   (if __name (setq _name __name)) _name)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; string _cmd
    4 (length _cmd)
    ;; geometry_msgs/Point _target
    (send _target :serialization-length)
    ;; string _name
    4 (length _name)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; string _cmd
       (write-long (length _cmd) s) (princ _cmd s)
     ;; geometry_msgs/Point _target
       (send _target :serialize s)
     ;; string _name
       (write-long (length _name) s) (princ _name s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; string _cmd
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _cmd (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; geometry_msgs/Point _target
     (send _target :deserialize buf ptr-) (incf ptr- (send _target :serialization-length))
   ;; string _name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get msgfile::FaceTarget :md5sum-) "186dafabee260d116e60117f4b2c786e")
(setf (get msgfile::FaceTarget :datatype-) "msgfile/FaceTarget")
(setf (get msgfile::FaceTarget :definition-)
      "Header header
string  cmd
geometry_msgs/Point target
string name
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :msgfile/FaceTarget "186dafabee260d116e60117f4b2c786e")


