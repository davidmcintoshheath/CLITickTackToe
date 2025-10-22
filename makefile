#Complier to use
CC := g++

#Locations
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
INC_DIR := include

#Executable name
EXE := $(BIN_DIR)/TickTackToe

#Src files
SRC := $(wildcard $(SRC_DIR)/*.cpp)

#Include files
INC := $(wildcard $(INC_DIR)/*.hpp)

#Obj files
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

#Flags
CPPFLAGS := -Iinclude -MMD -MP

CFLAGS := -Wall -Wextra

LDFLAGS := -L --verbose

LDLIBS :=

.PHONY: all clean run

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) -I$(INC_DIR) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR) #$(INC_DIR)/%.hpp
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR) #@ disables the echoing of the command

run: all
	@./$(EXE)

-include $(OBJ:.o=.d) #Dash silences errors
