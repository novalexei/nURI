
include_directories( ${gtest_SOURCE_DIR}/include)

set(TESTS uri_parse_test uri_set_test just_test uri_props_test uri_resnorm_test)

foreach (test ${TESTS})
    add_executable(${test} ${test}.cpp)
    add_dependencies(${test} nURI gtest_main)
    target_link_libraries(${test} nURI gtest_main)
    set_target_properties(${test} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${nURI_BINARY_DIR}/test)
    add_test(${test} ${nURI_BINARY_DIR}/test/${test})
endforeach (test)
