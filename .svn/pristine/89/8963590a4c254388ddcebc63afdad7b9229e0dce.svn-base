# Include Directories
include_directories( ${moldyn_SOURCE_DIR}/include )

set( CMAKE_MODULE_PATH
  ${moldyn_SOURCE_DIR}/cmake )

find_package( CPPUnit REQUIRED )

link_directories( ${moldyn_BINARY_DIR}/src )

add_executable( testRunner tests.cpp )

target_link_libraries( testRunner swap dl ${CPPUNIT_LIBRARIES} pthread )

include( GNUInstallDirs )

add_test( BasicTests testRunner )
