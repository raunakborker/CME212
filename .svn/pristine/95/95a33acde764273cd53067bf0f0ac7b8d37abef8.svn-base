# Find SWIG
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

# Find Python
find_package(PythonLibs 2.7 REQUIRED)
include_directories(${PYTHON_INCLUDE_PATH})

# Include Directories
include_directories(${moldyn_SOURCE_DIR}/include)

# Enable C++ support
set_source_files_properties(moldyn.i PROPERTIES CPLUSPLUS ON COMPILE_FLAGS "-std=c++11")

add_library( swap SHARED swap.cpp )

swig_add_module( moldyn python moldyn.i )

swig_link_libraries(moldyn ${PYTHON_LIBRARIES} swap)

file(COPY main.py config.yaml DESTINATION ${moldyn_BINARY_DIR}/src)
