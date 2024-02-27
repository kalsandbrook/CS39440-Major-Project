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
    src/data/game.h
    src/data/gamelibrary.cpp
    src/data/gamelibrary.h
    src/data/gamelibrarymodel.cpp
    src/data/gamelibrarymodel.h
    src/data/gamedatabase.h
    src/addgamedialog.cpp
    src/addgamedialog.h
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/gameitemdelegate.cpp
    src/gameitemdelegate.h
    src/gameview.cpp
    src/gameview.h
        src/data/gamedatabase.cpp
)

target_link_libraries(GamePile
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::Sql
)

#if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
#set(DEBUG_SUFFIX)
#if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
#set(DEBUG_SUFFIX "d")
#endif()
#set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
#if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
#set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
#if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
#set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
#endif()
#endif()
#if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#COMMAND ${CMAKE_COMMAND } - E make_directory
#"$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#COMMAND ${CMAKE_COMMAND } - E copy
#"${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
#"$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
#endif()
#foreach (QT_LIB Core Gui Widgets)
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#COMMAND ${CMAKE_COMMAND } - E copy
#"${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
#"$<TARGET_FILE_DIR:${PROJECT_NAME}>")
#endforeach(QT_LIB)
#endif()
