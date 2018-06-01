####################################################################################################################################################################################
# How this script works:
#####################################################################################################################################################################################
#
# This is a MAIN configuration script. The steps are:
#   1º  Set up cmake minimum version
#   2º  Check standard dependencies
#   3º  Configure MAIN project:     A)  Unique project name.
#                                   B)  Project solution.
#                                   C)  Internal global variables.
#
#   4º Add modules
#   5º Add samples
#
####################################################################################################################################################################################

# Project step I: Set up cmake minimum version
# ------------------------------------------------------------------------------------------------------
cmake_minimum_required (VERSION 2.8.12)

# Project step II: Check standard dependencies
# ------------------------------------------------------------------------------------------------------
include(CheckCXXCompilerFlag)
include(CheckCXXSourceRuns)

# Project step III: Configure MAIN project
# ------------------------------------------------------------------------------------------------------
set(PROJ_MAIN_NAME MEMDYNEDITION)

# Custom variables
set(${PROJ_MAIN_NAME}_PATH_MAIN 	     ${CMAKE_SOURCE_DIR} 					             CACHE PATH "This directory contains initial Path" )
set(${PROJ_MAIN_NAME}_PATH_LIBS 	     ${PROJECT_BINARY_DIR}/bin				             CACHE PATH "This directory contains all libs" )
set(${PROJ_MAIN_NAME}_PATH_EXE 		     ${PROJECT_BINARY_DIR}/bin				             CACHE PATH "This directory contains executables" )
set(${PROJ_MAIN_NAME}_PATH_3RDPARTY 	 ${CMAKE_SOURCE_DIR}/3rdParty 				         CACHE PATH "This directory contains 3rdparty libraries" )
set(${PROJ_MAIN_NAME}_PATH_INSTALL 	     ${PROJECT_BINARY_DIR}/install/${PROJ_MAIN_NAME} 	 CACHE PATH "This directory to install prebuilt" )
#set(${PROJ_MAIN_NAME}_PATH_RESOURCES  	 ${CMAKE_SOURCE_DIR}/resources 	                     CACHE PATH "This directory to provide data to your programs using a relative path" )
set(${PROJ_MAIN_NAME}_EXTRA_INCS "")

# Append core & dependencies
list(APPEND ${PROJ_MAIN_NAME}_EXTRA_INCS
    "${${PROJ_MAIN_NAME}_PATH_MAIN}/modules/core/include/"
    "${${PROJ_MAIN_NAME}_PATH_MAIN}/3rdParty/schifra/" )

# Official CMake variables
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${${PROJ_MAIN_NAME}_PATH_LIBS})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${${PROJ_MAIN_NAME}_PATH_LIBS})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${${PROJ_MAIN_NAME}_PATH_EXE})
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${${PROJ_MAIN_NAME}_PATH_INSTALL}" CACHE PATH "Changing default install path" FORCE)
endif()

# Info
message("CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")

# Project step IV: Add modules
# ------------------------------------------------------------------------------------------------------
add_subdirectory(modules)

# Project step V: Add samples
# ------------------------------------------------------------------------------------------------------
add_subdirectory(samples)
