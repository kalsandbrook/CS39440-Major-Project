cmake_minimum_required(VERSION 3.27)

project(GamePile)

option(BUILD_TESTS "Should tests be built?" ON)
option(BUILD_API_MODULE "Should the API Module be built?" OFF)

set(QT_MIN_VERSION "6.6.0")

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Lets Clangd (LSP Server) find includes
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# For GCC compiler
if (CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wconversion -Wsign-conversion")
endif()

find_package(Qt6 ${QT_MIN_VERSION} REQUIRED COMPONENTS
    Core
    Widgets
    Gui
    Sql
    Network
)

if (BUILD_TESTS)
    find_package(Qt6 ${QT_MIN_VERSION} REQUIRED COMPONENTS Test)
endif()

qt_standard_project_setup()

add_subdirectory(src)

if(BUILD_TESTS)
    add_subdirectory(test)
endif()


if(BUILD_API_MODULE) # The code for building the python API module. This is a bit bodged.

set(PYTHON_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/bin")
set(PYTHON_BUILD_SCRIPT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CS39440-Game-Pile-API/build.sh")
set(PYTHON_EXECUTABLE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CS39440-Game-Pile-API/dist/GamePile-API")

add_custom_command(
    OUTPUT ${PYTHON_EXECUTABLE_PATH}
    COMMAND ${SHELL_SCRIPT_PATH}
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/CS39440-Game-Pile-API"
    COMMENT "Running API Tool CLI - build.sh"
    VERBATIM
)

add_custom_target(GamePileAPI
    DEPENDS ${PYTHON_EXECUTABLE_PATH}
)

add_dependencies(GamePile GamePileAPI)

add_custom_command(
    TARGET GamePile
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${PYTHON_EXECUTABLE_PATH} ${CMAKE_CURRENT_BINARY_DIR}/GamePile-API
)

install(PROGRAMS ${PYTHON_EXECUTABLE_PATH}
    DESTINATION ${PYTHON_INSTALL_DIR}
)

endif()

install(FILES res/kas143.GamePile.desktop DESTINATION share/applications)
install(FILES res/GamePile.svg DESTINATION share/icons/hicolor/scalable/apps)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
