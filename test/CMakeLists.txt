set(COMMON_SOURCES
    ../src/data/game.cpp
    ../src/data/gameattributehelper.cpp
    ../src/data/gamehelper.cpp
    ../src/data/gamelibrary.cpp
    ../src/data/gamepileapi.cpp
    ../src/data/gameiconcontroller.cpp
    ../src/data/gamepileapiworker.cpp
    ../src/data/model/gamelibrarymodel.cpp
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

enable_testing()
function(create_test_executable TEST_NAME TEST_SOURCE)
    qt_add_executable(${TEST_NAME} ${TEST_SOURCE} ${COMMON_SOURCES})
    target_link_libraries(${TEST_NAME} PRIVATE Qt::Sql Qt::Core Qt::Gui Qt::Network Qt6::Test)

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()


create_test_executable(GamePile-test-GameLibrary test_gamelibrary.cpp)


