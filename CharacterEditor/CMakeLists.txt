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
		coredrvsview.ui
		characterprimaryattributeswidget.ui
		agegroupdisplayelement.ui
		abilitiesview.ui
		conditionsview.ui
		charactercombaticonview.ui
		characterprimarystatsview.ui
		itemsview.ui
		mainwindow.ui
		specialinfoview.ui
		spellsview.ui
		racestatsview.ui
		casteinfopanel.ui
		viewagingdialog.ui
		characterrepresentationselector.ui
		)


qt5_wrap_ui(UI_GENERATED_HEADERS ${UI_SOURCES})

add_executable(CharacterEditor
		characterrepresentationselector.cpp
		characterrepresentationselector.h
		coredrvsview.cpp
		coredrvsview.h
		characterprimaryattributeswidget.cpp
		characterprimaryattributeswidget.h
		agegroupdisplayelement.cpp
		agegroupdisplayelement.h
	abilitiesview.cpp
	abilitiesview.h
	charactercombaticonview.cpp
	charactercombaticonview.h
	characterprimarystatview.cpp
	characterprimarystatview.h
	conditionsview.cpp
	conditionsview.h
	itemsview.cpp
	itemsview.h
	main.cpp
	mainwindow.cpp
	mainwindow.h
	specialinfoview.cpp
	specialinfoview.h
	spellsview.cpp
	spellsview.h
		racestatsview.cpp
		racestatsview.h
		casteinfopanel.cpp
		casteinfopanel.h
		viewagingdialog.cpp
		viewagingdialog.h
	${UI_GENERATED_HEADERS}
	)

add_custom_command(
		TARGET CharacterEditor POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:CharacterEditor>/resources)
target_link_libraries(CharacterEditor
		Qt5::Widgets
		realmz
		realmzqt)
