#gcc -o icon icon.c -L/usr/X11/lib -lX11 -lstdc++
APP         := app
CCFLAGS     := -Wall -pedantic
CC          := g++
MKDIR       := mkdir -p
SRC         :=  src
OBJ         := obj

SUBDIRS := $(shell find $(SRC) -type d)
OBJSUBDIRS := $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))


.PHONY: dir

$(APP) : $(OBJSUBDIRS) $(SRC)/main.cpp
	$(CC) $(SRC)/main.cpp -c -o $(OBJ)/main.o $(CCFLAGS)

dir:
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))

$(OBJSUBDIRS):
	$(MKDIR) $(OBJSUBDIRS) 

dbg:
		@echo "debugger"
	$(info $(SRC)/main.cpp)

clean:
	$(RM) -r "./$(OBJ)"

cleanall: clean
	$(RM) "./$(APP)"
	
