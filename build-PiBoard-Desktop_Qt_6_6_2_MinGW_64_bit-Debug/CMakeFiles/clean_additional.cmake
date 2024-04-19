# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\PiBoard_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PiBoard_autogen.dir\\ParseCache.txt"
  "PiBoard_autogen"
  )
endif()
