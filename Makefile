CC=g++
CFLAGS=-c -Wall -std=c++17
LDFLAGS=
EXECUTABLE=game

COMMON_INC = .

SFML_SRC_PATH=src

SFML_WINDOWS_PATH=/MinGW
SFML_LINUX_PATH=/GCC
SFML_MACOS_PATH=/macOS

EXECUTABLE_NAME=app
SFML_BIN_PATH=

SFML_PATH=$(SFML_SRC_PATH)
ifeq ($(OS),Windows_NT)
	SFML_PATH=$(SFML_SRC_PATH)$(SFML_WINDOWS_PATH)
	EXECUTABLE=$(EXECUTABLE_NAME).exe
	SFML_BIN_PATH=$(SFML_PATH)/bin
else
	EXECUTABLE=$(EXECUTABLE_NAME)
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		SFML_PATH=$(SFML_SRC_PATH)$(SFML_LINUX_PATH)
	endif
	ifeq ($(UNAME_S),Darwin)
		SFML_PATH=$(SFML_SRC_PATH)$(SFML_MACOS_PATH)
	endif
endif

SFML_INC_PATH=$(SFML_PATH)/include
SFML_LIB_PATH=$(SFML_PATH)/lib

INC=-I$(SFML_INC_PATH) -I$(COMMON_INC)
LIB=-L$(SFML_LIB_PATH)

LIBS=-lsfml-graphics -lsfml-window -lsfml-system

SRCS=$(wildcard *.cpp) $(wildcard */*.cpp)
OBJS=$(patsubst %.cpp, $(ODIR)/%.o, $(SRCS))

ODIR=obj

PATH_WARDEN=\
mkdir -p obj; \
mkdir -p obj/core; \
mkdir -p obj/core; \
mkdir -p obj/util;

$(EXECUTABLE_NAME): $(OBJS)
	$(CC) $(OBJS) -o $(EXECUTABLE) $(LIB) $(LIBS)
	export LD_LIBRARY_PATH=SFML_LIB_PATH

ifeq ($(OS),Windows_NT)
	cp -a $(SFML_BIN_PATH)/*.dll ./
endif

	
$(ODIR)/%.o: %.cpp
	$(PATH_WARDEN)
	$(CC) $(CFLAGS) $(INC) $< -o $@

clean:
	rm -f $(EXECUTABLE)
	rm -f *.dll
	find . -type f -name "*.o" -delete