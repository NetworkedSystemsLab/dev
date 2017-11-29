
(cl:in-package :asdf)

(defsystem "serial_node-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Serial" :depends-on ("_package_Serial"))
    (:file "_package_Serial" :depends-on ("_package"))
  ))