cmake_minimum_required(VERSION 3.12.1)

project(tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(FRONT_HEADERS ../Headers/tests/frontend)
set(BACK_HEADERS ../Headers/tests/backend)

set(FRONT_SOURCE src/frontend)
set(BACK_SOURCE src/backend)

set(TEST_SOURCE_FRONT
			${FRONT_SOURCE}/test_MainWindow.cpp
			)

set(TEST_HEADERS_FRONT
			${FRONT_HEADERS}/test_MainWindow.hpp
			)

set(SOURCE
			src/main.cpp

			../src/MainWindow.cpp
			../src/Dialogs/QuitDialog.cpp
			)

set(HEADERS
			../Headers/MainWindow.hpp
			../Headers/Dialogs/QuitDialog.hpp
			)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Test REQUIRED)

add_executable(testfront 	${SOURCE} 
							${TEST_SOURCE_FRONT} 
							${HEADERS} 
							${TEST_HEADERS_FRONT}
							)

target_include_directories(testfront PRIVATE ../Headers)

target_link_libraries(testfront PRIVATE Qt5::Core)
target_link_libraries(testfront PRIVATE Qt5::Widgets)
target_link_libraries(testfront PRIVATE Qt5::Test)