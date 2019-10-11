;; Auto-generated. Do not edit!


(when (boundp 'msgfile::VoiceOrder)
  (if (not (find-package "MSGFILE"))
    (make-package "MSGFILE"))
  (shadow 'VoiceOrder (find-package "MSGFILE")))
(unless (find-package "MSGFILE::VOICEORDER")
  (make-package "MSGFILE::VOICEORDER"))

(in-package "ROS")
;;//! \htmlinclude VoiceOrder.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass msgfile::VoiceOrder
  :super ros::object
  :slots (_header _cmd _emotion _drinking _is_complete ))

(defmethod msgfile::VoiceOrder
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:cmd __cmd) "")
    ((:emotion __emotion) "")
    ((:drinking __drinking) "")
    ((:is_complete __is_complete) nil)
    )
   (send-super :init)
   (setq _header __header)
   (setq _cmd (string __cmd))
   (setq _emotion (string __emotion))
   (setq _drinking (string __drinking))
   (setq _is_complete __is_complete)
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
  (:emotion
   (&optional __emotion)
   (if __emotion (setq _emotion __emotion)) _emotion)
  (:drinking
   (&optional __drinking)
   (if __drinking (setq _drinking __drinking)) _drinking)
  (:is_complete
   (&optional __is_complete)
   (if __is_complete (setq _is_complete __is_complete)) _is_complete)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; string _cmd
    4 (length _cmd)
    ;; string _emotion
    4 (length _emotion)
    ;; string _drinking
    4 (length _drinking)
    ;; bool _is_complete
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; string _cmd
       (write-long (length _cmd) s) (princ _cmd s)
     ;; string _emotion
       (write-long (length _emotion) s) (princ _emotion s)
     ;; string _drinking
       (write-long (length _drinking) s) (princ _drinking s)
     ;; bool _is_complete
       (if _is_complete (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; string _cmd
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _cmd (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _emotion
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _emotion (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _drinking
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _drinking (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; bool _is_complete
     (setq _is_complete (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get msgfile::VoiceOrder :md5sum-) "c37634b59ea8bc295354a8112cf7bc4e")
(setf (get msgfile::VoiceOrder :datatype-) "msgfile/VoiceOrder")
(setf (get msgfile::VoiceOrder :definition-)
      "Header header
string  cmd
string  emotion
string  drinking
bool    is_complete
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



(provide :msgfile/VoiceOrder "c37634b59ea8bc295354a8112cf7bc4e")


