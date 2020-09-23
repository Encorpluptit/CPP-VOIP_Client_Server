# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Babel_qt_autogen"
  "CMakeFiles/Babel_qt_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Babel_qt_autogen.dir/ParseCache.txt"
  )
endif()
