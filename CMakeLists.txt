cmake_minimum_required(VERSION 3.28)
project(LearningCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Gui)
qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(LearningCPP
        src/main.cpp
        src/gameentry.cpp
        src/gameentry.h
        src/gamelist.cpp
        src/gamelist.h
)

qt_add_qml_module(learningCPP
        URI learningCPP
        QML_FILES
            src/main.qml
)

target_link_libraries(LearningCPP PRIVATE Qt6::Gui Qt6::Quick)

set_target_properties(LearningCPP PROPERTIES
        WIN32_EXECUTABLE ON
)

#add_executable(LearningCPP main.cpp)
