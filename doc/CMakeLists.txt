if(OS_MACOSX)
    # Add some directories to find the doxygen executable.
    set(ADDITIONAL_PATHS 
        /Developer/Applications/Doxygen.app/Contents/Resources 
        /Developer/Applications/Doxygen.app/Contents/MacOS 
        $ENV{HOME}/Applications/Doxygen.app/Contents/Resources 
        $ENV{HOME}/Applications/Doxygen.app/Contents/MacOS 
        $ENV{HOME}/Applications/Developer/Doxygen.app/Contents/Resources 
        $ENV{HOME}/Applications/Developer/Doxygen.app/Contents/MacOS)
 
    set(CMAKE_PROGRAM_PATH ${CMAKE_PROGRAM_PATH} ${ADDITIONAL_PATHS})
endif()

find_package(Doxygen REQUIRED)

# Set the doxygen input and output directories
set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR})
set(DOXYGEN_OUTPUT_DIR ${PROJECT_BINARY_DIR}/doc)

# Configure the source Doxyfile by copying it and replacing all @variables@
set(DOXYGEN_CONFIGURED_INPUT ${DOXYGEN_OUTPUT_DIR}/doxyfile)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doxyfile.in ${DOXYGEN_CONFIGURED_INPUT} @ONLY)

# Create the target
add_custom_target(doc ALL
                  COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIGURED_INPUT}
                  WORKING_DIRECTORY ${DOXYGEN_INPUT_DIR})

set_target_properties(doc PROPERTIES FOLDER "DOC")

# Set the install rule
install(DIRECTORY ${DOXYGEN_OUTPUT_DIR}/html
        DESTINATION doc/STP
        COMPONENT doc)
