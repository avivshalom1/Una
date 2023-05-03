THEME = exam_3

THEME2 = singly_linked_list
THEME3 = stack
THEME4 = bst
THEME5 = fsa
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
TARGET = ./$(THEME).out
VPATH =  ../../ds/src/$(THEME2)/ ../../ds/src/$(THEME3)/ ../../ds/src/$(THEME4)/ ../../sys_prog/src/$(THEME5)/ 

objects = $(THEME).o $(THEME2).o $(THEME3).o $(THEME4).o $(THEME5).o 
INCLUDE = -I../ds/include/ 

.PHONY: clean
.PHONY: debug
.PHONY: release
.PHONY: all
.PHONY: open
.PHONY: run
.PHONY: mkdir
.PHONY: cgdb

all : $(THEME).out


$(THEME).out: $(objects)
	$(CC) $(CFLAGS) $(THEME).o $(THEME2).o $(THEME3).o $(THEME4).o $(THEME5).o  -o$@
	
$(THEME).o: $(THEME).c 
	$(CC) $(CFLAGS)  -c $(THEME).c  -o$@	
	
$(THEME2).o: $(THEME2).c 
	$(CC) $(CFLAGS) -I. -c ../../ds/src/$(THEME2)/$(THEME2).c  -o$@
	
$(THEME3).o: $(THEME3).c 
	$(CC) $(CFLAGS) -I. -c ../../ds/src/$(THEME3)/$(THEME3).c  -o$@
	
$(THEME4).o: $(THEME4).c
	$(CC) $(CFLAGS) -I. -c ../../ds/src/$(THEME4)/$(THEME4).c  -o$@	

$(THEME5).o: $(THEME5).c
	$(CC) $(CFLAGS) -I. -c ../../sys_prog/src/$(THEME5)/$(THEME5).c  -o$@


debug: CFLAGS += -DEBUG
debug: all

release: CFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -o3
release: all
	
run: 
	$(TARGET)
		
valgrind: 
	valgrind ../../bin/$(THEME).out		
		
cgdb:
	cgdb $(TARGET)	
	
	
	
	
	
	
