# Install script for directory: /Users/lvjiaming/WorkSpace/OPGL/OPGL-test-clion-learnopgl/OPGL-test-clion

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/lvjiaming/WorkSpace/OPGL/OPGL-test-clion-learnopgl/OPGL-test-clion/build/openl_lib/cmake_install.cmake")
  include("/Users/lvjiaming/WorkSpace/OPGL/OPGL-test-clion-learnopgl/OPGL-test-clion/build/hello_window/cmake_install.cmake")
  include("/Users/lvjiaming/WorkSpace/OPGL/OPGL-test-clion-learnopgl/OPGL-test-clion/build/hello_triangle/cmake_install.cmake")
  include("/Users/lvjiaming/WorkSpace/OPGL/OPGL-test-clion-learnopgl/OPGL-test-clion/build/rectangle/cmake_install.cmake")
  include("/Users/lvjiaming/WorkSpace/OPGL/OPGL-test-clion-learnopgl/OPGL-test-clion/build/C++_base_test/cmake_install.cmake")
  include("/Users/lvjiaming/WorkSpace/OPGL/OPGL-test-clion-learnopgl/OPGL-test-clion/build/shader/cmake_install.cmake")
  include("/Users/lvjiaming/WorkSpace/OPGL/OPGL-test-clion-learnopgl/OPGL-test-clion/build/matrix/cmake_install.cmake")
  include("/Users/lvjiaming/WorkSpace/OPGL/OPGL-test-clion-learnopgl/OPGL-test-clion/build/texture/cmake_install.cmake")
  include("/Users/lvjiaming/WorkSpace/OPGL/OPGL-test-clion-learnopgl/OPGL-test-clion/build/coordinate/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/lvjiaming/WorkSpace/OPGL/OPGL-test-clion-learnopgl/OPGL-test-clion/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
