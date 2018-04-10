# Find SWIG
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

# Find Python
find_package(PythonLibs 2.7 REQUIRED)
include_directories(${PYTHON_INCLUDE_PATH})

# Specify where to look for include directories
include_directories(${PIVCExtension_SOURCE_DIR}/code)

# file pivcext.i and source file pivcext.c
swig_add_module(pivcext python pivcext.i pivcext.c)

# Link in the Python libraries
swig_link_libraries(pivcext ${PYTHON_LIBRARIES})

# Copy /code to the build directory
file(COPY main.py piv.py image.py DESTINATION ${PIVCExtension_BINARY_DIR}/code)

