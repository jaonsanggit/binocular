# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "msgfile: 3 messages, 0 services")

set(MSG_I_FLAGS "-Imsgfile:/home/sanghongrui/catkin_ws/src/msgfile/msg;-Igeometry_msgs:/opt/ros/kinetic/share/geometry_msgs/cmake/../msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(msgfile_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/sanghongrui/catkin_ws/src/msgfile/msg/VoiceOrder.msg" NAME_WE)
add_custom_target(_msgfile_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "msgfile" "/home/sanghongrui/catkin_ws/src/msgfile/msg/VoiceOrder.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/sanghongrui/catkin_ws/src/msgfile/msg/Core2Voice.msg" NAME_WE)
add_custom_target(_msgfile_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "msgfile" "/home/sanghongrui/catkin_ws/src/msgfile/msg/Core2Voice.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/sanghongrui/catkin_ws/src/msgfile/msg/FaceTarget.msg" NAME_WE)
add_custom_target(_msgfile_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "msgfile" "/home/sanghongrui/catkin_ws/src/msgfile/msg/FaceTarget.msg" "std_msgs/Header:geometry_msgs/Point"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(msgfile
  "/home/sanghongrui/catkin_ws/src/msgfile/msg/VoiceOrder.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msgfile
)
_generate_msg_cpp(msgfile
  "/home/sanghongrui/catkin_ws/src/msgfile/msg/Core2Voice.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msgfile
)
_generate_msg_cpp(msgfile
  "/home/sanghongrui/catkin_ws/src/msgfile/msg/FaceTarget.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msgfile
)

### Generating Services

### Generating Module File
_generate_module_cpp(msgfile
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msgfile
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(msgfile_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(msgfile_generate_messages msgfile_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sanghongrui/catkin_ws/src/msgfile/msg/VoiceOrder.msg" NAME_WE)
add_dependencies(msgfile_generate_messages_cpp _msgfile_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sanghongrui/catkin_ws/src/msgfile/msg/Core2Voice.msg" NAME_WE)
add_dependencies(msgfile_generate_messages_cpp _msgfile_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sanghongrui/catkin_ws/src/msgfile/msg/FaceTarget.msg" NAME_WE)
add_dependencies(msgfile_generate_messages_cpp _msgfile_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(msgfile_gencpp)
add_dependencies(msgfile_gencpp msgfile_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS msgfile_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(msgfile
  "/home/sanghongrui/catkin_ws/src/msgfile/msg/VoiceOrder.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msgfile
)
_generate_msg_eus(msgfile
  "/home/sanghongrui/catkin_ws/src/msgfile/msg/Core2Voice.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msgfile
)
_generate_msg_eus(msgfile
  "/home/sanghongrui/catkin_ws/src/msgfile/msg/FaceTarget.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msgfile
)

### Generating Services

### Generating Module File
_generate_module_eus(msgfile
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msgfile
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(msgfile_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(msgfile_generate_messages msgfile_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sanghongrui/catkin_ws/src/msgfile/msg/VoiceOrder.msg" NAME_WE)
add_dependencies(msgfile_generate_messages_eus _msgfile_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sanghongrui/catkin_ws/src/msgfile/msg/Core2Voice.msg" NAME_WE)
add_dependencies(msgfile_generate_messages_eus _msgfile_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sanghongrui/catkin_ws/src/msgfile/msg/FaceTarget.msg" NAME_WE)
add_dependencies(msgfile_generate_messages_eus _msgfile_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(msgfile_geneus)
add_dependencies(msgfile_geneus msgfile_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS msgfile_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(msgfile
  "/home/sanghongrui/catkin_ws/src/msgfile/msg/VoiceOrder.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msgfile
)
_generate_msg_lisp(msgfile
  "/home/sanghongrui/catkin_ws/src/msgfile/msg/Core2Voice.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msgfile
)
_generate_msg_lisp(msgfile
  "/home/sanghongrui/catkin_ws/src/msgfile/msg/FaceTarget.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msgfile
)

### Generating Services

### Generating Module File
_generate_module_lisp(msgfile
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msgfile
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(msgfile_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(msgfile_generate_messages msgfile_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sanghongrui/catkin_ws/src/msgfile/msg/VoiceOrder.msg" NAME_WE)
add_dependencies(msgfile_generate_messages_lisp _msgfile_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sanghongrui/catkin_ws/src/msgfile/msg/Core2Voice.msg" NAME_WE)
add_dependencies(msgfile_generate_messages_lisp _msgfile_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sanghongrui/catkin_ws/src/msgfile/msg/FaceTarget.msg" NAME_WE)
add_dependencies(msgfile_generate_messages_lisp _msgfile_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(msgfile_genlisp)
add_dependencies(msgfile_genlisp msgfile_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS msgfile_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(msgfile
  "/home/sanghongrui/catkin_ws/src/msgfile/msg/VoiceOrder.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msgfile
)
_generate_msg_nodejs(msgfile
  "/home/sanghongrui/catkin_ws/src/msgfile/msg/Core2Voice.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msgfile
)
_generate_msg_nodejs(msgfile
  "/home/sanghongrui/catkin_ws/src/msgfile/msg/FaceTarget.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msgfile
)

### Generating Services

### Generating Module File
_generate_module_nodejs(msgfile
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msgfile
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(msgfile_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(msgfile_generate_messages msgfile_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sanghongrui/catkin_ws/src/msgfile/msg/VoiceOrder.msg" NAME_WE)
add_dependencies(msgfile_generate_messages_nodejs _msgfile_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sanghongrui/catkin_ws/src/msgfile/msg/Core2Voice.msg" NAME_WE)
add_dependencies(msgfile_generate_messages_nodejs _msgfile_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sanghongrui/catkin_ws/src/msgfile/msg/FaceTarget.msg" NAME_WE)
add_dependencies(msgfile_generate_messages_nodejs _msgfile_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(msgfile_gennodejs)
add_dependencies(msgfile_gennodejs msgfile_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS msgfile_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(msgfile
  "/home/sanghongrui/catkin_ws/src/msgfile/msg/VoiceOrder.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msgfile
)
_generate_msg_py(msgfile
  "/home/sanghongrui/catkin_ws/src/msgfile/msg/Core2Voice.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msgfile
)
_generate_msg_py(msgfile
  "/home/sanghongrui/catkin_ws/src/msgfile/msg/FaceTarget.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msgfile
)

### Generating Services

### Generating Module File
_generate_module_py(msgfile
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msgfile
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(msgfile_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(msgfile_generate_messages msgfile_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sanghongrui/catkin_ws/src/msgfile/msg/VoiceOrder.msg" NAME_WE)
add_dependencies(msgfile_generate_messages_py _msgfile_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sanghongrui/catkin_ws/src/msgfile/msg/Core2Voice.msg" NAME_WE)
add_dependencies(msgfile_generate_messages_py _msgfile_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sanghongrui/catkin_ws/src/msgfile/msg/FaceTarget.msg" NAME_WE)
add_dependencies(msgfile_generate_messages_py _msgfile_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(msgfile_genpy)
add_dependencies(msgfile_genpy msgfile_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS msgfile_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msgfile)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/msgfile
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(msgfile_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(msgfile_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msgfile)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/msgfile
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(msgfile_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(msgfile_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msgfile)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/msgfile
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(msgfile_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(msgfile_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msgfile)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/msgfile
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(msgfile_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(msgfile_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msgfile)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msgfile\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/msgfile
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(msgfile_generate_messages_py geometry_msgs_generate_messages_py)
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(msgfile_generate_messages_py std_msgs_generate_messages_py)
endif()
