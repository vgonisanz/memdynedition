#####################################################################################################################################################################################
# This is an Auto-compilable sample configuration script.
# This CMakeLists user some macros to create executable and install following Pipero Style Project.
#     · This CMakeList is the reference .
#     · All headers (*.h, *.hcc) must be in ./include folder
#     · All source (*.c, *.cpp) must be in ./src folder
#
# The steps are:
#   1º  Assign temporal PROJ_NAME variable. Edit with a name and the sample will compile automatically.
#   2º  Assign INCLUDE_DIRECTORIES variable with all include paths needed by your code.
#   3º  Set linking directories (path to libraries needed)
#   4º  Macro to take all files, take all src and includes from their folders.
#   5º  Command ADD_EXECUTABLE create a executable according with your platform
#   6º  Linked libraries with sample. Set the name of libraries needed by the project
#   7º  Install: Where to install binaries
#
#   Warning: Variable ${PROJ_NAME} will be override out of this project.
#   Note: Uncomment macro PRINTBASICINFO if you have a problem with include or library path, or linking and get userful info in Cmake output.
#####################################################################################################################################################################################

# Sample step I: Set PROJ_NAME variable
# ------------------------------------------------------------------------------------------------------
set(PROJ_NAME playercrc32sample)
project(${PROJ_NAME})
message("+ Adding sample ${PROJ_NAME} ")

# Sample step II: Include directories with headers
# ------------------------------------------------------------------------------------------------------
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include )	    	              # This projects' includes
include_directories( ${${PROJ_MAIN_NAME}_PATH_MAIN}/modules/core/include/ )       # Core includes

# Sample step II: Create variables with all includes and sources
# ------------------------------------------------------------------------------------------------------
file(GLOB ${PROJ_NAME}_HEADERS
    "include/*.h"
    "include/*.hpp"
)
file(GLOB ${PROJ_NAME}_SRC
    "src/*.c"
    "src/*.cpp"
)

# Sample step III: Set linking directories (path to libraries needed)
# ------------------------------------------------------------------------------------------------------
#link_directories( ${DIR1} ${DIR2} ...)

# Sample step IV: Create executable with variables
# ------------------------------------------------------------------------------------------------------
add_executable(${PROJ_NAME} ${${PROJ_NAME}_HEADERS} ${${PROJ_NAME}_SRC} )

# Sample step V: Link libraries with sample. Set the name of libraries needed by the project
# ------------------------------------------------------------------------------------------------------
target_link_libraries(${PROJ_NAME} core)

# Sample step VI: Install: Where to install binaries
# ------------------------------------------------------------------------------------------------------
install(TARGETS ${PROJ_NAME}
        DESTINATION "${${PROJ_MAIN_NAME}_PATH_INSTALL}/${PROJ_NAME}/bin"
        )

#PRINTBASICINFO(${PROJ_NAME})						# Macro cmake_tools to print, uncomment to add info
message("- Sample ${PROJ_NAME} added!")				# Out info
