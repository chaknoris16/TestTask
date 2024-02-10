cmake_minimum_required(VERSION 3.5)

project(TestTask VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)
find_package(OpenCV REQUIRED)

set(PROJECT_SOURCES
    src/main.cpp

    src/mainwindow.cpp
    include/mainwindow.h
    ui/mainwindow.ui

    include/screenshot_comparison_widget.h
    src/screenshot_comparison_widget.cpp
    ui/screenshot_comparison_widget.ui

    include/screen_capture.h
    src/screen_capture.cpp

    include/db_manager.h
    src/db_manager.cpp

    include/imagecomparator.h
    src/imagecomparator.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TestTask
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

    )
endif()

target_link_libraries(TestTask PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                                             Qt${QT_VERSION_MAJOR}::Sql
                                               ${OpenCV_LIBS})

set_target_properties(TestTask PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS TestTask
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

