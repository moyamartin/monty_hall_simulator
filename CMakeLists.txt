#-------------------------------------------------------------------------------
#	CMAKE SETTINGS
#-------------------------------------------------------------------------------
CMAKE_MINIMUM_REQUIRED( VERSION 3.16 )
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

#needed to set project version
if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif()

#-------------------------------------------------------------------------------
#	PROJECT SETTINGS
#-------------------------------------------------------------------------------
SET( PROJ_NAME      "monty_hall_simulator" )
SET( PROJ_PATH      ${CMAKE_SOURCE_DIR} )
SET( PROJ_OUT_PATH  ${CMAKE_BINARY_DIR} )
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(BUILD_DOC "Build documentation" ON)
# not used for the moment
#SET( PROJ_LIBRARIES )
SET( PROJ_INCLUDES 
  inc
  ${CMAKE_BINARY_DIR}/exports
)
ADD_DEFINITIONS( -Dshared_EXPORTS )
PROJECT( ${PROJ_NAME} VERSION 0.0.1 )
ENABLE_TESTING()

#-------------------------------------------------------------------------------
#	SOURCE CODE
#-------------------------------------------------------------------------------
FILE( GLOB_RECURSE PROJ_SOURCES src/*.cpp )
FILE( GLOB_RECURSE PROJ_HEADERS inc/*.h )

ADD_SUBDIRECTORY( ${CMAKE_SOURCE_DIR}/test/ )

#-------------------------------------------------------------------------------
#	ADDITIONAL LIBRARIES
#-------------------------------------------------------------------------------
# LIST(APPEND LIBRARIES
#
# )
# 
# # Remove duplicate library dependencies. 
# LIST(REMOVE_DUPLICATES LIBRARIES) 

#-------------------------------------------------------------------------------
#	COMPILE FLAGS
#-------------------------------------------------------------------------------
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_STANDARD 11)

#-------------------------------------------------------------------------------
#	SOURCE GROUPS
#-------------------------------------------------------------------------------
source_group(generated REGULAR_EXPRESSION ".*_automoc.cpp")
source_group(resources REGULAR_EXPRESSION ".*[.][q]?rc")
source_group(source REGULAR_EXPRESSION ".*[.]cpp")
source_group(headers REGULAR_EXPRESSION ".*[.]h")
source_group(continuous-integration REGULAR_EXPRESSION ".*[.]yml")


#-------------------------------------------------------------------------------
#	EXTERNAL LIBRARIES
#-------------------------------------------------------------------------------
# fetch latest argparse
include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)


#-------------------------------------------------------------------------------
#	GENERATE EXECUTABLES
#-------------------------------------------------------------------------------
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
INCLUDE_DIRECTORIES( ${PROJ_INCLUDES} )
ADD_EXECUTABLE( ${PROJ_NAME} ${PROJ_SOURCES} ${PROJ_SOURC})
TARGET_LINK_LIBRARIES( ${PROJ_NAME} ${PROJ_LIBRARIES} argparse)

# Add debug postfix to executable name
SET_TARGET_PROPERTIES(${PROJ_NAME} PROPERTIES DEBUG_POSTFIX "-debug")

# Use the automatically determined RPATH values
set_target_properties(${PROJ_NAME} PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)

#-------------------------------------------------------------------------------
#	DEFINE INSTALL FOLDERS
#-------------------------------------------------------------------------------
IF(CMAKE_BUILD_TYPE MATCHES "Release")
    INSTALL(TARGETS ${PROJ_NAME}
        RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin/Release/
        LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/lib/Release/
        CONFIGURATIONS Release)
ELSE(CMAKE_BUILD_TYPE MATCHES "Debug")
    INSTALL(TARGETS ${PROJ_NAME}
        RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin/Debug/
        LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/lib/Debug/
        CONFIGURATIONS Debug)
ENDIF(CMAKE_BUILD_TYPE MATCHES "Release")

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
