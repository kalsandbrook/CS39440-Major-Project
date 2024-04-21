qt_add_executable(GamePile)

target_sources(GamePile PRIVATE

    main.cpp
    mainwindow.cpp


    data/model/gamelibrarymodel.cpp

    data/game.cpp

    data/gameattributehelper.cpp
    data/gamehelper.cpp
    data/gameiconhelper.cpp

    data/gamedatabase.cpp

    data/gamelibrary.cpp

    data/gamepileapi.cpp
    data/gamepileapiworker.cpp

    ui/attributefilter.cpp
    ui/filterswidget.cpp
    ui/statusfilter.cpp

    ui/gamedetailswidget.cpp

    ui/gameeditdialog.cpp
    ui/removablelistitemwidget.cpp
    ui/removableitemwidget.cpp


    ui/gameitemdelegate.cpp
    ui/gameview.cpp

    ui/gamelibraryproxymodel.cpp
)

target_link_libraries(GamePile PRIVATE
    Qt::Core
    Qt::Widgets
    Qt::Sql
    Qt::Network
)

install(TARGETS GamePile)
