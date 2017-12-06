// Auto-generated. Do not edit!

// (in-package serial_node.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Serial {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.speed_rpm = null;
      this.angle_degrees = null;
    }
    else {
      if (initObj.hasOwnProperty('speed_rpm')) {
        this.speed_rpm = initObj.speed_rpm
      }
      else {
        this.speed_rpm = 0;
      }
      if (initObj.hasOwnProperty('angle_degrees')) {
        this.angle_degrees = initObj.angle_degrees
      }
      else {
        this.angle_degrees = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Serial
    // Serialize message field [speed_rpm]
    bufferOffset = _serializer.int32(obj.speed_rpm, buffer, bufferOffset);
    // Serialize message field [angle_degrees]
    bufferOffset = _serializer.float32(obj.angle_degrees, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Serial
    let len;
    let data = new Serial(null);
    // Deserialize message field [speed_rpm]
    data.speed_rpm = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [angle_degrees]
    data.angle_degrees = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'serial_node/Serial';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '2369ae040ed10223d8b39ba1fe6713c2';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 speed_rpm
    float32 angle_degrees
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Serial(null);
    if (msg.speed_rpm !== undefined) {
      resolved.speed_rpm = msg.speed_rpm;
    }
    else {
      resolved.speed_rpm = 0
    }

    if (msg.angle_degrees !== undefined) {
      resolved.angle_degrees = msg.angle_degrees;
    }
    else {
      resolved.angle_degrees = 0.0
    }

    return resolved;
    }
};

module.exports = Serial;
