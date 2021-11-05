CXX := gcc
CSTD := c99
CFLAGS := -g -o3 -std=$(CSTD) -Wall -Wextra -Wpedantic -D_POSIX_C_SOURCE=199309L
INCLUDE_DIR := inc
CFLAGS := -I$(INCLUDE_DIR)

TARGET := main

INCLUDE_DIR := inc
SOURCE_DIR := src
OBJ_DIR := src/obj



_INCLUDES = time_pocess.h application.h
INCLUDES = $(patsubst %,$(INCLUDE_DIR)/%,$(_INCLUDES))

_OBJ = time_pocess.o application.o main.o
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))


.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(CFLAGS)

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c $(INCLUDES)
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(CFLAGS)

#remove build artifacts
.PHONY: clean 
clean:
		@echo Cleaning Up...
		-rm -fr $(TARGET) 2>/dev/null 
		-rm -fr $(TARGET).exe 2>/dev/null 
		-rm -fr *.o 2>/dev/null 
		-rm -f $(OBJ_DIR)/*.o 2>/dev/null			

.PHONY: run
run:
		./$(TARGET)	

.PHONY: gdb
gdb:
		gdb ./$(TARGET)		

