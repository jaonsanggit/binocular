; Auto-generated. Do not edit!


(cl:in-package msgfile-msg)


;//! \htmlinclude FaceTarget.msg.html

(cl:defclass <FaceTarget> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (cmd
    :reader cmd
    :initarg :cmd
    :type cl:string
    :initform "")
   (target
    :reader target
    :initarg :target
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point)))
)

(cl:defclass FaceTarget (<FaceTarget>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FaceTarget>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FaceTarget)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msgfile-msg:<FaceTarget> is deprecated: use msgfile-msg:FaceTarget instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <FaceTarget>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msgfile-msg:header-val is deprecated.  Use msgfile-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'cmd-val :lambda-list '(m))
(cl:defmethod cmd-val ((m <FaceTarget>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msgfile-msg:cmd-val is deprecated.  Use msgfile-msg:cmd instead.")
  (cmd m))

(cl:ensure-generic-function 'target-val :lambda-list '(m))
(cl:defmethod target-val ((m <FaceTarget>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msgfile-msg:target-val is deprecated.  Use msgfile-msg:target instead.")
  (target m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FaceTarget>) ostream)
  "Serializes a message object of type '<FaceTarget>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'cmd))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'cmd))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'target) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FaceTarget>) istream)
  "Deserializes a message object of type '<FaceTarget>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'cmd) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'cmd) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'target) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FaceTarget>)))
  "Returns string type for a message object of type '<FaceTarget>"
  "msgfile/FaceTarget")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FaceTarget)))
  "Returns string type for a message object of type 'FaceTarget"
  "msgfile/FaceTarget")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FaceTarget>)))
  "Returns md5sum for a message object of type '<FaceTarget>"
  "04a005a5867c4d41196138f92451713b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FaceTarget)))
  "Returns md5sum for a message object of type 'FaceTarget"
  "04a005a5867c4d41196138f92451713b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FaceTarget>)))
  "Returns full string definition for message of type '<FaceTarget>"
  (cl:format cl:nil "Header header~%string  cmd~%geometry_msgs/Point target~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FaceTarget)))
  "Returns full string definition for message of type 'FaceTarget"
  (cl:format cl:nil "Header header~%string  cmd~%geometry_msgs/Point target~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FaceTarget>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:length (cl:slot-value msg 'cmd))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'target))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FaceTarget>))
  "Converts a ROS message object to a list"
  (cl:list 'FaceTarget
    (cl:cons ':header (header msg))
    (cl:cons ':cmd (cmd msg))
    (cl:cons ':target (target msg))
))
