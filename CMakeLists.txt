cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project(HomeAccounting LANGUAGES CXX)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Sql)

set(PROJECT_HEADERS
    mainwindow.h
    loginwindow.h
    dbfasade.h)

set(PROJECT_SOURCES 
    main.cpp
    mainwindow.cpp
    loginwindow.cpp
    dbfasade.cpp)

qt5_wrap_cpp(PROJECT_SOURCES_MOC ${PROJECT_HEADERS})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECT_SOURCES_MOC})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    Qt5::Sql)