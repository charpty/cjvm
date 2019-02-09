include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(AllInstrctionTest ins/InsStackUnitTest.cpp)

target_link_libraries(AllInstrctionTest gtest gtest_main)