#gcc -o icon icon.c -L/usr/X11/lib -lX11 -lstdc++
CC := g++
LIBS := -Wall -pedantic
APP := app
MAIN_CPP := main.cpp
OBJ := main.o
MKDIR := mkdir -ps
SRC :=  src

SUB_DIR_FOLDERS := src/obj src/obj
CHECK_SUB_DIR_FOLDERS := $(shell find src/ -type d)


SUBDIRS := $(shell find $(SRC) -type d)
OBJSUBDIRS := $(patsubs $(SRC)%,$(OBJ)%,$(M_SUB_DIR_FOLDERS))


#M_SUB_DIR_FOLDERS := $(shell find $(SRC) -type d)
#O_SUB_DIR_FOLDERS := $(patsubst %/dir1,%/dir2%,$(M_SUB_DIR_FOLDERS))

#(patsubst (dir1)%,(dir2)%,(dir3)) # patsubst (carpeta1)% , (nombre de carpeta 2 se cambia por carpeta1)% ,(en carpeta))

## CLEAN rules

.PHONY: dir

$(APP) : main.cpp # APP depende de main.cpp
	$(CC) main.cpp -c -o $(LIBS)
#	$(CC) -o $(APP)  main.o 

create_dir:
	echo "create_dir"
	$( info $(SUB_DIR_FOLDERS))

check_dir:
	echo "check_dir"
	$( info $(CHECK_SUB_DIR_FOLDERS))

sub_dir:
	$( info $(M_SUB_DIR_FOLDERS))
	$( info $(O_SUB_DIR_FOLDERS))

dir:
	$(info $(SUBDIRS))
	$(INFO $(OBJSUBDIRS))
obj:
	

clean:
	$(RM) -r "./$(OBJ)"

cleanall: clean
	$(RM) "./$(APP)"
	
