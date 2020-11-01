cmake_minimum_required(VERSION 3.17)
project(QT5Elements)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
#set(UI_SOURCES )

#qt5_wrap_ui(UI_GENERATED_HEADERS ${UI_SOURCES})

add_library(realmzqt
        #${UI_GENERATED_HEADERS}
        PortraitModel.cc PortraitModel.h TacticalsModel.cc TacticalsModel.h ApplicationUtilities.h ApplicationUtilities.cc RepresentationModel.h RepresentationModel.cc ViewAgingTableModel.cc ViewAgingTableModel.h)

target_link_libraries(realmzqt Qt5::Widgets
        realmz)
