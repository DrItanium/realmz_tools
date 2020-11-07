cmake_minimum_required(VERSION 3.17)
project(RealmzCharacterViewer)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
set(UI_SOURCES
		mainwindow.ui
		)


qt5_wrap_ui(UI_GENERATED_HEADERS ${UI_SOURCES})

add_executable(CharacterViewer
	main.cpp
	mainwindow.cpp
	mainwindow.h
	${UI_GENERATED_HEADERS}
	)

add_custom_command(
		TARGET CharacterViewer POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:CharacterViewer>/resources)
target_link_libraries(CharacterViewer
		Qt5::Widgets
		realmz
		realmzqt)
