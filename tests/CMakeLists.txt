file(GLOB TESTS_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

foreach(FILE_PATH ${TESTS_SRC})
    get_filename_component(FILE_NAME ${FILE_PATH} NAME_WE)
    set(TEST_TARGET "Test_${FILE_NAME}")
    add_executable(${TEST_TARGET} ${FILE_PATH})
    set_target_properties(${TEST_TARGET} PROPERTIES
                          OUTPUT_NAME ${FILE_NAME})
    target_link_libraries(${TEST_TARGET} ${PROJECT_NAME})
    set(TESTS ${TESTS} ${TEST_TARGET})
endforeach()

add_custom_command(
    TARGET ${TESTS} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets"
)

set_property(TARGET ${TESTS} PROPERTY FOLDER "Tests")
