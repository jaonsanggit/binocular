
(cl:in-package :asdf)

(defsystem "ros_cv_proxy-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "FaceTarget" :depends-on ("_package_FaceTarget"))
    (:file "_package_FaceTarget" :depends-on ("_package"))
  ))