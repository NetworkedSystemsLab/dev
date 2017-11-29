;; Auto-generated. Do not edit!


(when (boundp 'serial_node::Serial)
  (if (not (find-package "SERIAL_NODE"))
    (make-package "SERIAL_NODE"))
  (shadow 'Serial (find-package "SERIAL_NODE")))
(unless (find-package "SERIAL_NODE::SERIAL")
  (make-package "SERIAL_NODE::SERIAL"))

(in-package "ROS")
;;//! \htmlinclude Serial.msg.html


(defclass serial_node::Serial
  :super ros::object
  :slots (_speed_rpm _angle_degrees ))

(defmethod serial_node::Serial
  (:init
   (&key
    ((:speed_rpm __speed_rpm) 0)
    ((:angle_degrees __angle_degrees) 0.0)
    )
   (send-super :init)
   (setq _speed_rpm (round __speed_rpm))
   (setq _angle_degrees (float __angle_degrees))
   self)
  (:speed_rpm
   (&optional __speed_rpm)
   (if __speed_rpm (setq _speed_rpm __speed_rpm)) _speed_rpm)
  (:angle_degrees
   (&optional __angle_degrees)
   (if __angle_degrees (setq _angle_degrees __angle_degrees)) _angle_degrees)
  (:serialization-length
   ()
   (+
    ;; int32 _speed_rpm
    4
    ;; float32 _angle_degrees
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _speed_rpm
       (write-long _speed_rpm s)
     ;; float32 _angle_degrees
       (sys::poke _angle_degrees (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _speed_rpm
     (setq _speed_rpm (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _angle_degrees
     (setq _angle_degrees (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get serial_node::Serial :md5sum-) "2369ae040ed10223d8b39ba1fe6713c2")
(setf (get serial_node::Serial :datatype-) "serial_node/Serial")
(setf (get serial_node::Serial :definition-)
      "int32 speed_rpm
float32 angle_degrees

")



(provide :serial_node/Serial "2369ae040ed10223d8b39ba1fe6713c2")


