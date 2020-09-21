CC := cc
OUTPUT := maya
PREFIX := /usr/local
CFLAGS := -Os -g3 -std=c99
LIBRARIES := -lm -lrt -lc
LDFLAGS :=
CXXEXTENSIONS ?= TRUE
ifeq ($(CXXEXTENSIONS), TRUE)
	CXX := c++
	#LIBRARIES += /usr/lib/libboost_system.a /usr/lib/libboost_filesystem.a
	LIBRARIES += -lboost_system -lboost_filesystem
	CXXFLAGS := -Os -g3 -std=c++17 
	LD := $(CXX)
else
	CFLAGS += -DBOOST_EXTENSIONS=0 -DFUNCTIONAL_EXTENSIONS=0
	LD := $(CC)
endif
COMMAND_PROMPT := "maya> "
BANNER_STRING := "\"     maya (based off of CLIPS \" VERSION_STRING \" \" CREATION_DATE_STRING \". Built on \" __DATE__ \" at \" __TIME__ \")\n\""

