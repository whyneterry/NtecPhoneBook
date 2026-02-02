#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "oatpp::oatpp-swagger" for configuration "Debug"
set_property(TARGET oatpp::oatpp-swagger APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(oatpp::oatpp-swagger PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/oatpp-1.4.0/oatpp-swagger.lib"
  )

list(APPEND _cmake_import_check_targets oatpp::oatpp-swagger )
list(APPEND _cmake_import_check_files_for_oatpp::oatpp-swagger "${_IMPORT_PREFIX}/lib/oatpp-1.4.0/oatpp-swagger.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
