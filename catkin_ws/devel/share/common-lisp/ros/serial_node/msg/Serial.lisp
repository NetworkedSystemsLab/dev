; Auto-generated. Do not edit!


(cl:in-package serial_node-msg)


;//! \htmlinclude Serial.msg.html

(cl:defclass <Serial> (roslisp-msg-protocol:ros-message)
  ((speed_rpm
    :reader speed_rpm
    :initarg :speed_rpm
    :type cl:integer
    :initform 0)
   (angle_degrees
    :reader angle_degrees
    :initarg :angle_degrees
    :type cl:float
    :initform 0.0))
)

(cl:defclass Serial (<Serial>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Serial>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Serial)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name serial_node-msg:<Serial> is deprecated: use serial_node-msg:Serial instead.")))

(cl:ensure-generic-function 'speed_rpm-val :lambda-list '(m))
(cl:defmethod speed_rpm-val ((m <Serial>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader serial_node-msg:speed_rpm-val is deprecated.  Use serial_node-msg:speed_rpm instead.")
  (speed_rpm m))

(cl:ensure-generic-function 'angle_degrees-val :lambda-list '(m))
(cl:defmethod angle_degrees-val ((m <Serial>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader serial_node-msg:angle_degrees-val is deprecated.  Use serial_node-msg:angle_degrees instead.")
  (angle_degrees m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Serial>) ostream)
  "Serializes a message object of type '<Serial>"
  (cl:let* ((signed (cl:slot-value msg 'speed_rpm)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'angle_degrees))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Serial>) istream)
  "Deserializes a message object of type '<Serial>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'speed_rpm) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angle_degrees) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Serial>)))
  "Returns string type for a message object of type '<Serial>"
  "serial_node/Serial")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Serial)))
  "Returns string type for a message object of type 'Serial"
  "serial_node/Serial")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Serial>)))
  "Returns md5sum for a message object of type '<Serial>"
  "2369ae040ed10223d8b39ba1fe6713c2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Serial)))
  "Returns md5sum for a message object of type 'Serial"
  "2369ae040ed10223d8b39ba1fe6713c2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Serial>)))
  "Returns full string definition for message of type '<Serial>"
  (cl:format cl:nil "int32 speed_rpm~%float32 angle_degrees~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Serial)))
  "Returns full string definition for message of type 'Serial"
  (cl:format cl:nil "int32 speed_rpm~%float32 angle_degrees~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Serial>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Serial>))
  "Converts a ROS message object to a list"
  (cl:list 'Serial
    (cl:cons ':speed_rpm (speed_rpm msg))
    (cl:cons ':angle_degrees (angle_degrees msg))
))
