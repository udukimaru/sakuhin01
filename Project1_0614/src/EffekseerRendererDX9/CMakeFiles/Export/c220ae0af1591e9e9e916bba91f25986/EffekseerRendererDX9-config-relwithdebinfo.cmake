#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "EffekseerRendererDX9" for configuration "RelWithDebInfo"
set_property(TARGET EffekseerRendererDX9 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(EffekseerRendererDX9 PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/EffekseerRendererDX9.lib"
  )

list(APPEND _cmake_import_check_targets EffekseerRendererDX9 )
list(APPEND _cmake_import_check_files_for_EffekseerRendererDX9 "${_IMPORT_PREFIX}/lib/EffekseerRendererDX9.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
