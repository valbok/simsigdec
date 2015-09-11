set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(ScannerTest ScannerTest.cpp)
target_link_libraries(ScannerTest gtest core Qt5::Core)

add_executable(configTest configTest.cpp)
target_link_libraries(configTest gtest core Qt5::Core)

