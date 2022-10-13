


file(GLOB_RECURSE ALL_TEST_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(tests ${ALL_TEST_FILES})
target_link_libraries(tests PUBLIC Boost::headers Boost::container rt)
