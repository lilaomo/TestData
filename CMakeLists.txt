cmake_minimum_required(VERSION 3.16)

project(CMakeQml VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appCMakeQml
    main.cpp
)

qt_add_qml_module(appCMakeQml
    URI CMakeQml
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES ImportData.h
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appCMakeQml PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appCMakeQml
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appCMakeQml
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appCMakeQml
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
