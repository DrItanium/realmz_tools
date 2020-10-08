cmake_minimum_required(VERSION 3.17)
project(RealmzCharacterEditor)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
set(UI_SOURCES
	abilitiesview.ui
	conditionsview.ui
	charactercombaticonview.ui
	characterprimarystatsview.ui
	iconselect6.ui
	itemsview.ui
	mainwindow.ui
	specialinfoview.ui
	spellsview.ui)


qt5_wrap_ui(UI_GENERATED_HEADERS ${UI_SOURCES})

add_executable(CharacterEditor
	abilitiesview.cpp
	abilitiesview.h
	charactercombaticonview.cpp
	charactercombaticonview.h
	characterprimarystatview.cpp
	characterprimarystatview.h
	conditionsview.cpp
	conditionsview.h
	iconselect6.cpp
	iconselect6.h
	itemsview.cpp
	itemsview.h
	main.cpp
	mainwindow.cpp
	mainwindow.h
	specialinfoview.cpp
	specialinfoview.h
	spellsview.cpp
	spellsview.h
	${UI_GENERATED_HEADERS}
	)

target_link_libraries(CharacterEditor Qt5::Widgets)
