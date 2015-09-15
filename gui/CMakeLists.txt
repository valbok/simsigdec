add_library(gui
    mainwindow.cpp
)

add_executable(Simsigdec main.cpp)
target_link_libraries(Simsigdec gui core Qt5::Widgets Qt5::Network)
