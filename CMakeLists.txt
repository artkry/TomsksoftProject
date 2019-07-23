cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project(HomeAccounting LANGUAGES CXX)

set(CMAKE_AUTORCC ON)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Sql)

set(PROJECT_HEADERS 
    mainwindow.h
    loginwindow.h
    registrationwindow.h
    daywidget.h
    editform.h
    aboutwindow.h
    instructionwindow.h
    dbsingleton.h)

set(PROJECT_SOURCES
    mainwindow.cpp
    loginwindow.cpp
    registrationwindow.cpp
    main.cpp
    daywidget.cpp
    editform.cpp
    aboutwindow.cpp
    instructionwindow.cpp
    dbsingleton.cpp)


qt5_add_resources(PROJECT_RESOURCES
    res.qrc)

qt5_wrap_cpp(PROJECT_SOURCES_MOC ${PROJECT_HEADERS})

add_executable(${PROJECT_NAME} 
    ${PROJECT_SOURCES} 
    ${PROJECT_HEADERS} 
    ${PROJECT_SOURCES_MOC} 
    ${PROJECT_RESOURCES})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    Qt5::Sql)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)