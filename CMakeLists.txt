cmake_minimum_required(VERSION 3.5)

project(PiBoard VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        gaia.cpp
        gaia.h
        gaia.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PiBoard
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        hermes.h hermes.cpp hermes.ui
        hephaestus.h hephaestus.cpp hephaestus.ui
        resources.qrc
        artemis.h artemis.cpp
        minerva.h minerva.cpp
        PrometheusThread.h PrometheusThread.cpp
        EpimetheusThread.h EpimetheusThread.cpp
        Epimetheus.h Epimetheus.cpp
        Prometheus.h Prometheus.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET PiBoard APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(PiBoard SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(PiBoard
            ${PROJECT_SOURCES}
        )
    endif()
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    target_link_libraries(PiBoard PRIVATE Qt${QT_VERSION_MAJOR}::Widgets wiringPi)
else()
    target_link_libraries(PiBoard PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
endif()


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.PiBoard)
endif()
set_target_properties(PiBoard PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS PiBoard
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PiBoard)
endif()
