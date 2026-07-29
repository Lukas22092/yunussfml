set(TEST_TARGET ${PROJECT_NAME}_tests)

find_package(GTest CONFIG REQUIRED)

add_executable(${TEST_TARGET} test_main.cpp)

target_compile_options(${TEST_TARGET} PRIVATE
    -g -Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align
    -Wunused -Woverloaded-virtual -Wconversion -Wsign-conversion -Wnull-dereference
    -Wdouble-promotion -Wformat=2
    -stdlib=libc++)

set_property(TARGET ${TEST_TARGET} PROPERTY CXX_STANDARD 26)
set_property(TARGET ${TEST_TARGET} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${TEST_TARGET} PROPERTY CXX_EXTENSIONS OFF)

target_include_directories(${TEST_TARGET} PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${TEST_TARGET} PRIVATE
    GTest::gtest
    GTest::gtest_main
    Boost::asio
    Boost::beast)

add_test(NAME ${TEST_TARGET} COMMAND ${TEST_TARGET})
