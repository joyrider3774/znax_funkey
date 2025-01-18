DEBUG = 1
SRC_DIR = src
OBJ_DIR = ./obj
EXE=znax

SRC=$(wildcard *.c $(foreach fd, $(SRC_DIR), $(fd)/*.c)) 
OBJS=$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))


CXX ?= gcc
SDLCONFIG ?= sdl-config
CXXFLAGS ?= -Os -Wall -Wextra -Wno-write-strings
LDFLAGS ?= -lSDL_image -lSDL_ttf -lSDL_mixer -lmikmod -lSDL_gfx -lm

ifdef DEBUG
CXXFLAGS += -g
endif

ifdef TARGET
include $(TARGET).mk
endif

CXXFLAGS += `$(SDLCONFIG) --cflags`
LDFLAGS += `$(SDLCONFIG) --libs`

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(TARGET_ARCH) $^ $(LDFLAGS) -o $@ 

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	$(RM) -rv *~ $(OBJS) $(EXE)