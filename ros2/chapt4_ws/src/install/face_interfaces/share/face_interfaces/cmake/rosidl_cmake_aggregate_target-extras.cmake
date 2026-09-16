# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target face_interfaces::face_interfaces
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${face_interfaces_TARGETS}.
if(face_interfaces_TARGETS AND NOT TARGET face_interfaces::face_interfaces)
  add_library(face_interfaces::face_interfaces INTERFACE IMPORTED)
  set_target_properties(face_interfaces::face_interfaces PROPERTIES
    INTERFACE_LINK_LIBRARIES "${face_interfaces_TARGETS}")
endif()
