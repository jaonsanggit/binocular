;; Auto-generated. Do not edit!


(when (boundp 'msgfile::Core2Voice)
  (if (not (find-package "MSGFILE"))
    (make-package "MSGFILE"))
  (shadow 'Core2Voice (find-package "MSGFILE")))
(unless (find-package "MSGFILE::CORE2VOICE")
  (make-package "MSGFILE::CORE2VOICE"))

(in-package "ROS")
;;//! \htmlinclude Core2Voice.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass msgfile::Core2Voice
  :super ros::object
  :slots (_header _cmd _name _gender _age ))

(defmethod msgfile::Core2Voice
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:cmd __cmd) "")
    ((:name __name) "")
    ((:gender __gender) "")
    ((:age __age) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _cmd (string __cmd))
   (setq _name (string __name))
   (setq _gender (string __gender))
   (setq _age (round __age))
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
  (:name
   (&optional __name)
   (if __name (setq _name __name)) _name)
  (:gender
   (&optional __gender)
   (if __gender (setq _gender __gender)) _gender)
  (:age
   (&optional __age)
   (if __age (setq _age __age)) _age)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; string _cmd
    4 (length _cmd)
    ;; string _name
    4 (length _name)
    ;; string _gender
    4 (length _gender)
    ;; uint16 _age
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; string _cmd
       (write-long (length _cmd) s) (princ _cmd s)
     ;; string _name
       (write-long (length _name) s) (princ _name s)
     ;; string _gender
       (write-long (length _gender) s) (princ _gender s)
     ;; uint16 _age
       (write-word _age s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; string _cmd
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _cmd (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _gender
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _gender (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; uint16 _age
     (setq _age (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get msgfile::Core2Voice :md5sum-) "c1551c43ce95816519cdce6766a6a75b")
(setf (get msgfile::Core2Voice :datatype-) "msgfile/Core2Voice")
(setf (get msgfile::Core2Voice :definition-)
      "Header header
string cmd
string name
string gender
uint16 age 
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

")



(provide :msgfile/Core2Voice "c1551c43ce95816519cdce6766a6a75b")


