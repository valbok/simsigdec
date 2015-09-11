add_library(gui
    mainwindow.cpp
)

add_executable(Simsigdec main.cpp)
target_link_libraries(Simsigdec gui objects core Qt5::Widgets)
