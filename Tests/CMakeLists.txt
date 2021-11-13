project(testbench_tests)

set(SOURCE_FILE_SUFFIXES *.c *.cpp *.h *.hpp)
set(TEST_FILE_SUFFIXES *.cc)

function(glob_code_files_in_directory out_list directory suffix_list)
    foreach(suffix ${suffix_list})
        file(GLOB_RECURSE FOUND_FILES ${directory}/${suffix})
        list(APPEND TEMP_LIST ${FOUND_FILES})
    endforeach()
    set(${out_list} ${TEMP_LIST} PARENT_SCOPE)
endfunction()


add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR})

set(OG_PROJECT_SRC_DIR ${CMAKE_SOURCE_DIR})
include_directories(${OG_PROJECT_SRC_DIR}/src)

glob_code_files_in_directory(TEST_UTILS_FILE_LIST
                             ${CMAKE_CURRENT_LIST_DIR}/TestUtils
                             "${SOURCE_FILE_SUFFIXES}")


# Tests/TestUtils
glob_code_files_in_directory(TEST_TEST_UTILS_FILE_LIST
                             ${CMAKE_CURRENT_LIST_DIR}/TestUtils/Tests
                             "${TEST_FILE_SUFFIXES}")
list(APPEND TEST_FILE_LIST ${TEST_TEST_UTILS_FILE_LIST})
add_executable(test_test_utils ${TEST_TEST_UTILS_FILE_LIST} ${TEST_UTILS_FILE_LIST})
target_link_libraries(test_test_utils gtest gtest_main)

# src/xmarco_stuff
set(OG_XMACRO_INCLUDE_LIST ${OG_PROJECT_SRC_DIR}/${XMACRO_INCLUDE_LIST})
set(TEST_XMACRO_FILE_LIST shadow_src/xmacro_stuff/test_xmacro_definitions.cc)
list(APPEND OG_INCLUDE_LIST ${OG_XMACRO_INCLUDE_LIST})
list(APPEND TEST_FILE_LIST ${TEST_XMACRO_FILE_LIST})
add_executable(test_xmacro ${TEST_XMACRO_FILE_LIST} ${TEST_UTILS_FILE_LIST} ${OG_XMACRO_INCLUDE_LIST})
target_link_libraries(test_xmacro gtest gtest_main)

# src/Utils
set(OG_UTILS_INCLUDE_LIST ${OG_PROJECT_SRC_DIR}/${UTILS_INCLUDE_LIST})
set(TEST_UTILS_FILE_LIST shadow_src/Utils/test_constexpr_utils.cc)
list(APPEND OG_INCLUDE_LIST ${OG_UTILS_INCLUDE_LIST})
list(APPEND TEST_FILE_LIST ${TEST_UTILS_FILE_LIST})
add_executable(test_Utils ${TEST_UTILS_FILE_LIST} ${TEST_UTILS_FILE_LIST} ${OG_UTILS_INCLUDE_LIST})
target_link_libraries(test_Utils gtest gtest_main)

# all tests
add_executable(Google_Tests_run ${TEST_FILE_LIST} ${TEST_UTILS_FILE_LIST} ${OG_INCLUDE_LIST})
target_link_libraries(Google_Tests_run gtest gtest_main)