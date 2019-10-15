// Auto-generated. Do not edit!

// (in-package msgfile.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class VoiceOrder {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.emotion = null;
      this.DrinkName = null;
      this.CupNum = null;
      this.Temp = null;
      this.OrderFinish = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('emotion')) {
        this.emotion = initObj.emotion
      }
      else {
        this.emotion = '';
      }
      if (initObj.hasOwnProperty('DrinkName')) {
        this.DrinkName = initObj.DrinkName
      }
      else {
        this.DrinkName = '';
      }
      if (initObj.hasOwnProperty('CupNum')) {
        this.CupNum = initObj.CupNum
      }
      else {
        this.CupNum = '';
      }
      if (initObj.hasOwnProperty('Temp')) {
        this.Temp = initObj.Temp
      }
      else {
        this.Temp = '';
      }
      if (initObj.hasOwnProperty('OrderFinish')) {
        this.OrderFinish = initObj.OrderFinish
      }
      else {
        this.OrderFinish = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type VoiceOrder
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [emotion]
    bufferOffset = _serializer.string(obj.emotion, buffer, bufferOffset);
    // Serialize message field [DrinkName]
    bufferOffset = _serializer.string(obj.DrinkName, buffer, bufferOffset);
    // Serialize message field [CupNum]
    bufferOffset = _serializer.string(obj.CupNum, buffer, bufferOffset);
    // Serialize message field [Temp]
    bufferOffset = _serializer.string(obj.Temp, buffer, bufferOffset);
    // Serialize message field [OrderFinish]
    bufferOffset = _serializer.bool(obj.OrderFinish, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type VoiceOrder
    let len;
    let data = new VoiceOrder(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [emotion]
    data.emotion = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [DrinkName]
    data.DrinkName = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [CupNum]
    data.CupNum = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [Temp]
    data.Temp = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [OrderFinish]
    data.OrderFinish = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += object.emotion.length;
    length += object.DrinkName.length;
    length += object.CupNum.length;
    length += object.Temp.length;
    return length + 17;
  }

  static datatype() {
    // Returns string type for a message object
    return 'msgfile/VoiceOrder';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '665c610b7c2ad0cdb9e8600f1fe3adc6';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new VoiceOrder(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.emotion !== undefined) {
      resolved.emotion = msg.emotion;
    }
    else {
      resolved.emotion = ''
    }

    if (msg.DrinkName !== undefined) {
      resolved.DrinkName = msg.DrinkName;
    }
    else {
      resolved.DrinkName = ''
    }

    if (msg.CupNum !== undefined) {
      resolved.CupNum = msg.CupNum;
    }
    else {
      resolved.CupNum = ''
    }

    if (msg.Temp !== undefined) {
      resolved.Temp = msg.Temp;
    }
    else {
      resolved.Temp = ''
    }

    if (msg.OrderFinish !== undefined) {
      resolved.OrderFinish = msg.OrderFinish;
    }
    else {
      resolved.OrderFinish = false
    }

    return resolved;
    }
};

module.exports = VoiceOrder;
