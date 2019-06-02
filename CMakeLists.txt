cmake_minimum_required(VERSION 3.5)

project(3DSceneCreator)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
# Handle qrc file
set(CMAKE_AUTORCC ON)
# C++ compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# Find the Qt libraries
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

find_package(Qt5Core)
# Sources files
set(SOURCE_FILES
        src/main.cpp
        src/geometry.cpp
        src/mainwidget.cpp
        src/geometryengine.cpp
        src/mainwindow.cpp
        src/mainwindow.ui
        ressources/shaders.qrc
        )


# Create executable from sources
add_executable(3DSceneCreator ${SOURCE_FILES})
# Linking libraries
target_link_libraries(3DSceneCreator Qt5::Core Qt5::Widgets)