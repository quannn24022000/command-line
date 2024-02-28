.PHONY: clean all .ONESHELL

#make run shell without escape and semicolon - oneshell
.ONESHELL:

#not echo command
.SILENT:

#global build tool
CC:=gcc
LIBS:=-lm
CFLAGS=-g -Wall

#global directory variable
ORG_DIR:=mgmt
SRC_DIR:=$(ORG_DIR)/src
OBJ_DIR:=$(ORG_DIR)/obj
BIN_DIR:=$(ORG_DIR)/bin

#source directory
SRC_CMDSH  =$(SRC_DIR)/cmdshell
SRC_CMDMGMT=$(SRC_DIR)/cmdmgmt
SRC_ITMGMT =$(SRC_DIR)/itmgmt
SRC_INTERN =$(SRC_DIR)/intern
SRC_TOPIC  =$(SRC_DIR)/topic
SRC_CORE   =$(SRC_DIR)/core
SRC_CFG    =$(SRC_DIR)/cfg
SRC_LIB    =$(SRC_DIR)/lib

#update CFLAGS. CFLAGS will contain all header file directory, so we use it to contain function prototype
CFLAGS+=-I$(SRC_CMDSH) -I$(SRC_CMDMGMT) -I$(SRC_ITMGMT) -I$(SRC_INTERN) -I$(SRC_TOPIC) -I$(SRC_CORE) -I$(SRC_CFG) -I$(SRC_LIB)

#object directory
OBJ_CMDSH  =$(OBJ_DIR)/cmdshell
OBJ_CMDMGMT=$(OBJ_DIR)/cmdmgmt
OBJ_ITMGMT =$(OBJ_DIR)/itmgmt
OBJ_INTERN =$(OBJ_DIR)/intern
OBJ_TOPIC  =$(OBJ_DIR)/topic
OBJ_CORE   =$(OBJ_DIR)/core
OBJ_CFG    =$(OBJ_DIR)/cfg
OBJ_LIB	   =$(OBJ_DIR)/lib

#source file
SRC_CMDSH_C  =$(wildcard $(SRC_CMDSH)/*.c)
SRC_CMDMGMT_C=$(wildcard $(SRC_CMDMGMT)/*.c)
SRC_ITMGMT_C =$(wildcard $(SRC_ITMGMT)/*.c)
SRC_INTERN_C =$(wildcard $(SRC_INTERN)/*.c)
SRC_TOPIC_C  =$(wildcard $(SRC_TOPIC)/*.c)
SRC_CORE_C   =$(wildcard $(SRC_CORE)/*.c)
SRC_CFG_C    =$(wildcard $(SRC_CFG)/*.c)
SRC_LIB_C    =$(wildcard $(SRC_LIB)/*.c)

#header file
SRC_CMDSH_H  =$(wildcard $(SRC_CMDSH)/*.h)
SRC_CMDMGMT_H=$(wildcard $(SRC_CMDMGMT)/*.h)
SRC_ITMGMT_H =$(wildcard $(SRC_ITMGMT)/*.h)
SRC_INTERN_H =$(wildcard $(SRC_INTERN)/*.h)
SRC_TOPIC_H  =$(wildcard $(SRC_TOPIC)/*.h)
SRC_CORE_H   =$(wildcard $(SRC_CORE)/*.h)
SRC_CFG_H    =$(wildcard $(SRC_CFG)/*.h)
SRC_LIB_H    =$(wildcard $(SRC_LIB)/*.h)

#object file
#OBJ_CMDSH_O  =$(patsubst $(SRC_CMDSH)/%.c, $(OBJ_CMDSH)/%.o, $(SRC_CMDSH_C))
OBJ_CMDSH_O  =$(addprefix $(OBJ_CMDSH)/,$(notdir $(patsubst %.c,%.o,$(SRC_CMDSH_C))))
OBJ_CMDMGMT_O=$(addprefix $(OBJ_CMDMGMT)/,$(notdir $(patsubst %.c,%.o,$(SRC_CMDMGMT_C))))
OBJ_ITMGMT_O =$(addprefix $(OBJ_ITMGMT)/,$(notdir $(patsubst %.c,%.o,$(SRC_ITMGMT_C))))
OBJ_INTERN_O =$(addprefix $(OBJ_INTERN)/,$(notdir $(patsubst %.c,%.o,$(SRC_INTERN_C))))
OBJ_TOPIC_O  =$(addprefix $(OBJ_TOPIC)/,$(notdir $(patsubst %.c,%.o,$(SRC_TOPIC_C))))
OBJ_CORE_O   =$(addprefix $(OBJ_CORE)/,$(notdir $(patsubst %.c,%.o,$(SRC_CORE_C))))
OBJ_CFG_O    =$(addprefix $(OBJ_CFG)/,$(notdir $(patsubst %.c,%.o,$(SRC_CFG_C))))
OBJ_LIB_O    =$(addprefix $(OBJ_LIB)/,$(notdir $(patsubst %.c,%.o,$(SRC_LIB_C))))

#build target 
TARGET_NAME:=mgmt
TARGET:=$(BIN_DIR)/$(TARGET_NAME)

#clean    : remove all files made by make
#distclean: remove all files made by make and configured files by ./configure
all: clean distclean obj_folder $(TARGET)
	@echo Succesfully build project!!!

clean:
	@echo Cleaning all objects and target file made by make!!!
	rm -rf $(OBJ_CMDSH)/*.o $(OBJ_CMDMGMT)/*.o $(OBJ_ITMGMT)/*.o $(OBJ_INTERN)/*.o $(OBJ_TOPIC)/*.o $(OBJ_CORE)/*.o $(OBJ_CFG)/*.o $(OBJ_LIB)/*.o
	rm -rf $(TARGET)

distclean: clean
	@echo Distclean clean additional obj directory compared with make clean!!!
	rm -rf $(OBJ_DIR)

obj_folder:
	@if [ -d $(OBJ_DIR) ]; then
		echo $(OBJ_DIR) is already created!!!
	else
		@echo Create object directory folder
		mkdir $(OBJ_DIR)
	fi

#build executable file need all object files to link them into executable
# $@: for left hand \
  $<: for first right hand \
  $^: for all right hand

$(TARGET): $(OBJ_CMDSH_O) $(OBJ_CMDMGMT_O) $(OBJ_ITMGMT_O) $(OBJ_INTERN_O) $(OBJ_TOPIC_O) $(OBJ_CORE_O) $(OBJ_CFG_O) $(OBJ_LIB_O)
	@echo Assembling all object files into target application...
	$(CC) $(CFLAGS) -o $@ $^

#build object file just need HEADER files from other folder so use $(CFLAGS) to INCLUDE those header file to get function prototype
$(OBJ_CMDSH)/%.o: $(SRC_CMDSH)/%.c $(SRC_CMDSH_H) $(SRC_LIB_H)
	@echo "Build intern object file"
	if [ -d $(OBJ_CMDSH) ]; then
	    @echo Folder is already created
	else
		@echo Create object folder of CMDSH
		mkdir $(OBJ_CMDSH)
	fi
	#$(CC) $(CFLAGS) -c $< -o $@
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_CMDMGMT)/%.o: $(SRC_CMDMGMT)/%.c $(SRC_CMDMGMT_H) $(SRC_LIB_H)
	@echo "Build intern object file"
	if [ -d $(OBJ_CMDMGMT) ]; then
	    echo Folder is already created
	else
		mkdir $(OBJ_CMDMGMT)
	fi
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_ITMGMT)/%.o: $(SRC_ITMGMT)/%.c $(SRC_ITMGMT_H) $(SRC_LIB_H)
	@echo "Build intern object file"
	if [ -d $(OBJ_ITMGMT) ]; then
	    echo Folder is already created
	else
		mkdir $(OBJ_ITMGMT)
	fi
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_INTERN)/%.o: $(SRC_INTERN)/%.c $(SRC_INTERN_H) $(SRC_LIB_H)
	@echo "Build intern object file"
	if [ -d $(OBJ_INTERN) ]; then
	    echo Folder is already created
	else
		mkdir $(OBJ_INTERN)
	fi
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_TOPIC)/%.o: $(SRC_TOPIC)/%.c $(SRC_TOPIC_H) $(SRC_LIB_H)
	@echo "Build topic object file"
	if [ -d $(OBJ_TOPIC) ]; then
		echo Folder is already created
	else
		mkdir $(OBJ_TOPIC)
	fi
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_CORE)/%.o: $(SRC_CORE)/%.c $(SRC_CORE_H) $(SRC_LIB_H)
	@echo "Build core object file"
	if [ -d $(OBJ_CORE) ]; then
		echo Folder is already created
	else
		mkdir $(OBJ_CORE)
	fi
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_CFG)/%.o: $(SRC_CFG)/%.c $(SRC_CFG_H) $(SRC_LIB_H)
	@echo "Build cfg object file"
	if [ -d $(OBJ_CFG) ]; then
		echo Folder is already created
	else
		mkdir $(OBJ_CFG)
	fi
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_LIB)/%.o: $(SRC_LIB)/%.c $(SRC_LIB_H)
	@echo "Build lib object file"
	if [ -d $(OBJ_LIB) ]; then
		echo Folder is already created
	else
		mkdir $(OBJ_LIB)
	fi
	$(CC) $(CFLAGS) -o $@ -c $<

#NOTE: gcc -o [output file] -c [source C file to specific build object file not linker]


#Step by step to make this project:
	#Step 1: Make all C source files seperated in their folder into object file (without linker)
	#Step 2: Link all those object files into target executable file

	#Note: To compile C source file in one folder into object file we need source C files and header H files of that folder is enough \
		   - If one or many C source file of that folder call to another functions of other folder ---> we just need include header files \
			of that folder only\
			Example: Build folder A and folder A have a C file call to one function of b C file in folder B. So we just need header file \
			of folder B. In header file declared for prototype of that function is enough. After that use -I to include those header file \
			into build of A folder. File source a just need header file of b header to build into object file. In case of OBJECT file we \
			just need header file

	#Note: - To build OBJECT file      ---> Just need HEADER file to get prototype \
		   - To build EXECUTABLE file  ---> Need both HEADER file and SOURCE file to link them in to EXECUTABLE file

	#Example: File main.c use function func() in libds.c \
		   - To build main.c source file into object file main.o ---> We just need include libds.h (contain function prototype) into main.c \
			and compile gcc -c main.c so we have main.o without error. But if we build C file into executable main.o file with gcc main.c, the \
			error will happen \
	       - To build main.c source file into executable file    ---> We need build libds.c file into object file, main.c into object file also \
			and after that linking them into executable file
