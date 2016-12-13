#################################################
# Anthony Islas
# Date Created: 31 Aug 2016
# Last Revised: 31 Aug 2016
# Description: This makefile is generic to build
# an executable from specified directories
#################################################

INCLUDE = ./RubiksCube
LIB_DIRS = 
CC = gcc -std=gnu99
CPP = g++

vpath %.h $(INCLUDE)
vpath %.cpp $(INCLUDE)

CDEFS = 
CFLAGS = -I$(INCLUDE) $(CDEFS)
DEBUGFLAGS = -O0 -g -Wall -pedantic
LIBS =
CVLIBS = `pkg-config --libs opencv` -L/usr/lib -lopencv_core -lopencv_flann -lopencv_video

# Things to build
#
PRODUCT = rubiks
ifeq ($(OS), Windows_NT)
	PRODUCT_EXT = .exe
else
	PRODUCT_EXT = 
endif

# Directories for libraries and objects
OBJS_DIR = ./obj
LIB_DIR = 


# Dependencies
_DEPS = 
DEPS = $(patsubst %, $(INDLUDE_DIRS)/%,$(_DEPS))

# Objects product depends on
# List all objects to make HERE!!! <- Order matters
_OBJ =  sticker.o pieces.o rface.o stringsplit.o rcube.o main.o
OBJ = $(patsubst %, $(OBJS_DIR)/%,$(_OBJ))

# MAKE All
all: ${PRODUCT}

# Rule for making executables
rubiks: $(OBJ)
	@echo Executable type: $(PRODUCT_EXT) 
	@mkdir -p $(OBJS_DIR)
	$(CPP) $(LDFLAGS) $(CFLAGS) $(DEBUGFLAGS) -o $@$(PRODUCT_EXT) $^ $(LIBS)
	
	
rubiksCV: CDEFS = -DOPENCV 
rubiksCV: LIBS += $(CVLIBS)
rubiksCV: $(OBJS_DIR)/rcubeOpenCV.o
rubiksCV: $(OBJS_DIR)/rcubeOpenCV.o $(OBJ)
	@echo Executable type: $(PRODUCT_EXT) 
	@mkdir -p $(OBJS_DIR)
	$(CPP) $(LDFLAGS) $(CFLAGS) $(DEBUGFLAGS) -o $@$(PRODUCT_EXT) $^ $(LIBS)
 
  
#Protect files called $@
.PHONY: clean

clean: 
	-rm -f $(OBJS_DIR)/*.o
	-rm -f *.o *~ core $(INCLUDE_DIRS)/*~
	-rm ${PRODUCT}$(PRODUCT_EXT)  

depend:

obj: $(OBJS_DIR)
	@mkdir -p $@
  
# Rules for generating .o from .cpp and .c files
$(OBJS_DIR)/%.o: %.cpp $(DEPS)
	$(CPP) -c  -o $@ $< $(DEBUGFLAGS) $(CFLAGS)
  
$(OBJS_DIR)/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c -o $@ $<
