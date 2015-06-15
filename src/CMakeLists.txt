cmake_minimum_required (VERSION 2.8)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(BUILD_SHARED_LIB
    "Build raspboop as a shared library." ON)

# Very few files, just hard code it in
set(HEADER_FILES Command.h Commandable.h Server.h Config.h)
set(SOURCE_FILES Command.cpp Server.cpp)

include_directories(${CMAKE_SOURCE_DIR}/src)

find_package(Boost 1.56 COMPONENTS system regex REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

if(BUILD_SHARED_LIB)
  if(WIN32)
    add_definitions(-DRBPCOM_EXPORTS)
  endif()
  add_library(${TARGET} SHARED ${HEADER_FILES} ${SOURCE_FILES})
else()
  add_definitions(-DRBPCOM_STATIC)
  add_library(${TARGET} STATIC ${HEADER_FILES} ${SOURCE_FILES})
endif()

set_property(TARGET ${TARGET} PROPERTY CXX_STANDARD 11)

target_link_libraries(${TARGET} ${Boost_LIBRARIES})

set_target_properties(${TARGET} PROPERTIES PUBLIC_HEADER "${HEADER_FILES}")
set_target_properties(${TARGET} PROPERTIES FOLDER raspboop-com)

if(INSTALL_SDK)
  install(TARGETS ${TARGET}
    # IMPORTANT: Add the foo library to the "export-set"
    EXPORT RBPCOMTargets
    RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
    LIBRARY DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
    ARCHIVE DESTINATION "${INSTALL_LIB_DIR}" COMPONENT lib
    PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/${TARGET}"
      COMPONENT dev)
endif()
