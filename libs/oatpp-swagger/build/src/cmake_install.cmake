# Install script for directory: C:/Users/user/Downloads/NtecPhoneBook-main/libs/oatpp-swagger/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/oatpp-swagger")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/oatpp-1.4.0" TYPE STATIC_LIBRARY FILES "C:/Users/user/Downloads/NtecPhoneBook-main/libs/oatpp-swagger/build/src/Debug/oatpp-swagger.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/oatpp-1.4.0" TYPE STATIC_LIBRARY FILES "C:/Users/user/Downloads/NtecPhoneBook-main/libs/oatpp-swagger/build/src/Release/oatpp-swagger.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/oatpp-1.4.0" TYPE STATIC_LIBRARY FILES "C:/Users/user/Downloads/NtecPhoneBook-main/libs/oatpp-swagger/build/src/MinSizeRel/oatpp-swagger.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/oatpp-1.4.0" TYPE STATIC_LIBRARY FILES "C:/Users/user/Downloads/NtecPhoneBook-main/libs/oatpp-swagger/build/src/RelWithDebInfo/oatpp-swagger.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/oatpp-1.4.0/oatpp-swagger" TYPE DIRECTORY FILES "C:/Users/user/Downloads/NtecPhoneBook-main/libs/oatpp-swagger/cmake/../src/oatpp-swagger" FILES_MATCHING REGEX "/[^/]*\\.hpp$")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/oatpp-swagger-1.4.0/oatpp-swaggerTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/oatpp-swagger-1.4.0/oatpp-swaggerTargets.cmake"
         "C:/Users/user/Downloads/NtecPhoneBook-main/libs/oatpp-swagger/build/src/CMakeFiles/Export/02ce27050210de5c19584ba4395d9d37/oatpp-swaggerTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/oatpp-swagger-1.4.0/oatpp-swaggerTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/oatpp-swagger-1.4.0/oatpp-swaggerTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/oatpp-swagger-1.4.0" TYPE FILE FILES "C:/Users/user/Downloads/NtecPhoneBook-main/libs/oatpp-swagger/build/src/CMakeFiles/Export/02ce27050210de5c19584ba4395d9d37/oatpp-swaggerTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/oatpp-swagger-1.4.0" TYPE FILE FILES "C:/Users/user/Downloads/NtecPhoneBook-main/libs/oatpp-swagger/build/src/CMakeFiles/Export/02ce27050210de5c19584ba4395d9d37/oatpp-swaggerTargets-debug.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/oatpp-swagger-1.4.0" TYPE FILE FILES "C:/Users/user/Downloads/NtecPhoneBook-main/libs/oatpp-swagger/build/src/CMakeFiles/Export/02ce27050210de5c19584ba4395d9d37/oatpp-swaggerTargets-minsizerel.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/oatpp-swagger-1.4.0" TYPE FILE FILES "C:/Users/user/Downloads/NtecPhoneBook-main/libs/oatpp-swagger/build/src/CMakeFiles/Export/02ce27050210de5c19584ba4395d9d37/oatpp-swaggerTargets-relwithdebinfo.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/oatpp-swagger-1.4.0" TYPE FILE FILES "C:/Users/user/Downloads/NtecPhoneBook-main/libs/oatpp-swagger/build/src/CMakeFiles/Export/02ce27050210de5c19584ba4395d9d37/oatpp-swaggerTargets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/oatpp-swagger-1.4.0" TYPE FILE FILES
    "C:/Users/user/Downloads/NtecPhoneBook-main/libs/oatpp-swagger/build/src/oatpp-swaggerConfig.cmake"
    "C:/Users/user/Downloads/NtecPhoneBook-main/libs/oatpp-swagger/build/src/oatpp-swaggerConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/oatpp-1.4.0/bin/oatpp-swagger" TYPE DIRECTORY FILES "C:/Users/user/Downloads/NtecPhoneBook-main/libs/oatpp-swagger/src/../res" FILES_MATCHING REGEX "/[^/]*\\.[^/]*$")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/user/Downloads/NtecPhoneBook-main/libs/oatpp-swagger/build/src/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
