cmake_minimum_required(VERSION 3.27)
project(GamePile)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CLI_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/bin")
set(QT_EXECUTABLE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/bin")

set(PYTHON_BUILD_SCRIPT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CS39440-Game-Pile-API/build.sh")
set(EXECUTABLE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CS39440-Game-Pile-API/dist/GamePile-API")

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
        src/ui/statusfilter.cpp
        src/ui/statusfilter.h
        src/ui/attributefilter.cpp
        src/ui/attributefilter.h
        src/ui/removableitemwidget.h
        src/ui/removableitemwidget.cpp
        src/ui/removablelistwidgetitem.h
        src/ui/removablelistwidgetitem.cpp
        src/ui/gamelibraryproxymodel.cpp
        src/ui/gamelibraryproxymodel.h
        src/ui/filterswidget.cpp
        src/ui/filterswidget.h
        src/data/gameiconcontroller.cpp
        src/data/gameiconcontroller.h
        src/data/gameattributehelper.cpp
        src/data/gameattributehelper.h
)

target_link_libraries(GamePile
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Sql
)

# Building and packaging Python CLI File

add_custom_command(
    OUTPUT ${EXECUTABLE_PATH}
    COMMAND ${SHELL_SCRIPT_PATH}
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/CS39440-Game-Pile-API"
    COMMENT "Running API Tool CLI - build.sh"
    VERBATIM
)

add_custom_target(BuildCLI
    DEPENDS ${EXECUTABLE_PATH}
)

add_dependencies(GamePile BuildCLI)

add_custom_command(
    TARGET GamePile
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${EXECUTABLE_PATH} ${CMAKE_CURRENT_BINARY_DIR}/GamePile-API
)

install(PROGRAMS ${EXECUTABLE_PATH}
    DESTINATION ${CLI_INSTALL_DIR}
)

# Install Main Program

install(TARGETS GamePile
        RUNTIME DESTINATION ${QT_EXECUTABLE_INSTALL_DIR}
)

# Desktop File.

set(DESKTOP_FILE_CONTENT "
[Desktop Entry]
Type=Application
Name=GamePile
Comment=A CS39440 Major Project, produced for Aberystwyth University by Kal Sandbrook (kas143).
Exec=GamePile
Terminal=false
Categories=Utility;Game;
")

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/GamePile.desktop "${DESKTOP_FILE_CONTENT}")

install(CODE
        "execute_process(
        COMMAND desktop-file-install --dir=${CMAKE_INSTALL_PREFIX}/share/applications ${CMAKE_CURRENT_BINARY_DIR}/GamePile.desktop
        )"
)
