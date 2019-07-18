cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project(HomeAccounting LANGUAGES CXX)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Sql)

set(PROJECT_HEADERS 
    mainwindow.h
    loginwindow.h
    registrationwindow.h
    dbfasade.h
    daywidget.h
    editform.h)

set(PROJECT_SOURCES
    mainwindow.cpp
    loginwindow.cpp
    registrationwindow.cpp
    dbfasade.cpp
    main.cpp
    daywidget.cpp
    editform.cpp)

qt5_wrap_cpp(PROJECT_SOURCES_MOC ${PROJECT_HEADERS})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECT_SOURCES_MOC})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    Qt5::Sql)