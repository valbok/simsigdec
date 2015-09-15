add_library(server
    Server.cpp
    Connection.cpp
    ThreadScanner.cpp
)

add_executable(Server main.cpp)
target_link_libraries(Server server core Qt5::Core Qt5::Widgets Qt5::Network)
