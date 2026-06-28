#gcc -o icon icon.c -L/usr/X11/lib -lX11 -lstdc++
#find /src -type f iname *.cpp
#find /src -type f name *.cpp

APP         := app
CCFLAGS     := -Wall -pedantic
CFLAGS     	:= $(CCFLAGS)
CC          := g++
C			:= gcc
MKDIR       := mkdir -p
SRC         :=  src
OBJ         := obj
ALLCPP 		:= $(shell find src/ -type f -iname *.cpp)
ALLC 		:= $(shell find src/ -type f -iname *.c)
ALLCS		:= $(shell find src/ -type f -iname *.c)
ALLCSOBJ	:= $(patsubst %.c,%.o,$(ALLCS))

SUBDIRS := $(shell find $(SRC) -type d)
OBJSUBDIRS := $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))


.PHONY: dir
#$(APP) : $(OBJSUBDIRS) $(ALLCSOBJ) $(SRC)/main.cpp
$(APP) : $(OBJSUBDIRS) $(ALLCSOBJ)
	$(CC) $(SRC)/main.cpp -c -o $(OBJ)/main.o $(CCFLAGS)



%.o : %.c
#	$(C) -o $@ -c $^ $(CCFLAGS)
	$(C) -o $(patsubst $(SRC)%,$(OBJ)%,$@) -c $^ $(CFLAGS)

dir:
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	

$(OBJSUBDIRS):
	$(MKDIR) $(OBJSUBDIRS) 

dbg:
#		@echo "debugger"
#$(info $(SRC)/main.cpp)
#	@echo "debugger all cpp"
#	$(info $(ALLCPP))
	$(info $(ALLCS))
	$(info $(ALLCSOBJ))

clean:
	$(RM) -r "./$(OBJ)"

cleanall: clean
	$(RM) "./$(APP)"
	
