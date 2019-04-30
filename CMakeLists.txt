#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)


# Make the scripts available in the 'cmake' directory available for the
# 'include()' command, 'find_package()' command.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
project(mat_example)



find_package(PyNE REQUIRED)


include_directories(${PYNE_INCLUDE_DIR})

# Find HDF5
MESSAGE("-- HDF5 Root: ${HDF5_ROOT}")
if(HDF5_ROOT)
  FIND_PACKAGE(HDF5 REQUIRED)
else()
  FIND_PACKAGE(HDF5)
endif()
if(NOT HDF5_FOUND AND NOT HDF5_ROOT)
  MESSAGE("--    HDF5 not found on empty HDF5_ROOT, "
          "setting to DEPS_ROOT_DIR: ${DEPS_ROOT_DIR}")
  set(HDF5_ROOT "${DEPS_ROOT_DIR}")
  FIND_PACKAGE(HDF5 REQUIRED)
endif()
ADD_DEFINITIONS(${HDF5_DEFINITIONS})
include_directories("${HDF5_INCLUDE_DIRS}")
if(NOT HDF5_LIBRARY_DIRS STREQUAL "")
  link_directories(${HDF5_LIBRARY_DIRS})
endif()
set(LIBS_HDF5 ${HDF5_C_LIBRARIES})
set(LIBS ${LIBS} ${HDF5_C_LIBRARIES})
MESSAGE("--    HDF5 Include directory: ${HDF5_INCLUDE_DIRS}")
MESSAGE("--    HDF5 Library directories: ${HDF5_LIBRARY_DIRS}")
MESSAGE("--    HDF5 Libraries: ${HDF5_C_LIBRARIES}")


#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(mat_ex ${sources} ${headers})
target_link_libraries(mat_ex ${Geant4_LIBRARIES} ${LIBS_HDF5}
    ${PYNE_LIBS_DIR}/libpyne.dylib)


#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#
add_custom_target(mat DEPENDS mat_ex)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS mat_ex DESTINATION bin)


