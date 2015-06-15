cmake_minimum_required (VERSION 2.8)
set(TARGET raspboop-com)
project(${TARGET})

# Version
set(RBPCOM_VERSION_MAJOR 0)
set(RBPCOM_VERSION_MINOR 1)
set(RBPCOM_PATCH_VERSION 0)
set(RBPCOM_VERSION
  ${RBPCOM_MAJOR_VERSION}.${RBPCOM_MINOR_VERSION}.${RBPCOM_PATCH_VERSION})

set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH
  "Installation directory for header files")

if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/CMake/${TARGET})
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
  "Installation directory for CMake files")
 
# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

option(INSTALL_SDK "Install the ${TARGET} sdk (header files and binaries)" ON)

add_subdirectory(src)

# Add all targets to the build-tree export set
export(TARGETS ${TARGET}
  FILE "${PROJECT_BINARY_DIR}/RBPCOMTargets.cmake")
 
# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE ${TARGET})
 
# Create the *Config.cmake and *ConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_INCLUDE_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(${TARGET}Config.cmake.in
  "${PROJECT_BINARY_DIR}/${TARGET}Config.cmake" @ONLY)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${${TARGET}_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(${TARGET}Config.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${TARGET}Config.cmake" @ONLY)
# ... for both
configure_file(${TARGET}ConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/${TARGET}ConfigVersion.cmake" @ONLY)
 

if(INSTALL_SDK)
  # Install the *Config.cmake and *ConfigVersion.cmake
  install(FILES
    "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${TARGET}Config.cmake"
    "${PROJECT_BINARY_DIR}/${TARGET}ConfigVersion.cmake"
    DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)
 
  # Install the export set for use with the install-tree
  install(EXPORT RBPCOMTargets DESTINATION
    "${INSTALL_CMAKE_DIR}" COMPONENT dev)
endif()










