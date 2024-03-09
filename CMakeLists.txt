cmake_minimum_required(VERSION 3.27)
project(GamePile)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(Qt6_DIR "C:/Qt/6.6.2/mingw_64/lib/cmake/Qt6")

find_package(Qt6 COMPONENTS
    Core
    Gui
    Widgets
    Sql
    REQUIRED
)

add_executable(GamePile
        src/main.cpp
        src/mainwindow.h
        src/mainwindow.cpp
        src/data/model/gamelibrarymodel.h
        src/data/model/gamelibrarymodel.cpp
        src/data/game.h
        src/data/game.cpp
        src/data/gamehelper.h
        src/data/gamehelper.cpp
        src/data/gamedatabase.h
        src/data/gamedatabase.cpp
        src/data/gamelibrary.h
        src/data/gamelibrary.cpp
        src/ui/gameitemdelegate.h
        src/ui/gameitemdelegate.cpp
        src/ui/gamedetailswidget.h
        src/ui/gamedetailswidget.cpp
        src/ui/gameeditdialog.h
        src/ui/gameeditdialog.cpp
        src/ui/gameview.h
        src/ui/gameview.cpp
        src/ui/searchbarwidget.h
        src/ui/searchbarwidget.cpp
)

target_link_libraries(GamePile
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Sql
)

