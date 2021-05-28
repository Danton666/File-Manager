cmake_minimum_required(VERSION 3.12.1)

project(Manager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 	COMPONENTS 
						Core 
						Widgets 
					REQUIRED)

set(HEADERS 
			Headers/MainWindow.hpp
			Headers/Dialogs/QuitDialog.hpp
			)

set(SOURCE
			src/main.cpp
			src/MainWindow.cpp
			src/Dialogs/QuitDialog.cpp
			)

add_definitions(-Wall -O2)

add_executable(Manager ${SOURCE} ${HEADERS})

target_include_directories(Manager PRIVATE Headers)

target_link_libraries(Manager PRIVATE 
								Qt5::Widgets 
								Qt5::Core)
