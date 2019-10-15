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
  :slots (_header _emotion _DrinkName _CupNum _Temp _OrderFinish ))

(defmethod msgfile::VoiceOrder
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:emotion __emotion) "")
    ((:DrinkName __DrinkName) "")
    ((:CupNum __CupNum) "")
    ((:Temp __Temp) "")
    ((:OrderFinish __OrderFinish) nil)
    )
   (send-super :init)
   (setq _header __header)
   (setq _emotion (string __emotion))
   (setq _DrinkName (string __DrinkName))
   (setq _CupNum (string __CupNum))
   (setq _Temp (string __Temp))
   (setq _OrderFinish __OrderFinish)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:emotion
   (&optional __emotion)
   (if __emotion (setq _emotion __emotion)) _emotion)
  (:DrinkName
   (&optional __DrinkName)
   (if __DrinkName (setq _DrinkName __DrinkName)) _DrinkName)
  (:CupNum
   (&optional __CupNum)
   (if __CupNum (setq _CupNum __CupNum)) _CupNum)
  (:Temp
   (&optional __Temp)
   (if __Temp (setq _Temp __Temp)) _Temp)
  (:OrderFinish
   (&optional __OrderFinish)
   (if __OrderFinish (setq _OrderFinish __OrderFinish)) _OrderFinish)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; string _emotion
    4 (length _emotion)
    ;; string _DrinkName
    4 (length _DrinkName)
    ;; string _CupNum
    4 (length _CupNum)
    ;; string _Temp
    4 (length _Temp)
    ;; bool _OrderFinish
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; string _emotion
       (write-long (length _emotion) s) (princ _emotion s)
     ;; string _DrinkName
       (write-long (length _DrinkName) s) (princ _DrinkName s)
     ;; string _CupNum
       (write-long (length _CupNum) s) (princ _CupNum s)
     ;; string _Temp
       (write-long (length _Temp) s) (princ _Temp s)
     ;; bool _OrderFinish
       (if _OrderFinish (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; string _emotion
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _emotion (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _DrinkName
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _DrinkName (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _CupNum
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _CupNum (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _Temp
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _Temp (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; bool _OrderFinish
     (setq _OrderFinish (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get msgfile::VoiceOrder :md5sum-) "665c610b7c2ad0cdb9e8600f1fe3adc6")
(setf (get msgfile::VoiceOrder :datatype-) "msgfile/VoiceOrder")
(setf (get msgfile::VoiceOrder :definition-)
      "Header header
string  emotion
string  DrinkName
string  CupNum
string  Temp
bool    OrderFinish
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



(provide :msgfile/VoiceOrder "665c610b7c2ad0cdb9e8600f1fe3adc6")


