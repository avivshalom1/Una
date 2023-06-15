VAR := $(patsubst %.c,%, $(wildcard *.c))

CC = g++
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
LDFLAGS = -Wl,-rpath,/home/evi95/github/projects/lib/

IDIR = /home/evi95/github/projects/include/
TDIR = /home/evi95/github/projects/test/
ODIR = /home/evi95/github/projects/obj/
BDIR = /home/evi95/github/projects/bin/
LDIR = /home/evi95/github/projects/lib/

VPATH = $(IDIR) $(TDIR) $(ODIR) $(BDIR) $(LDIR)


TARGET = $(BDIR)$(VAR).out
OBJ = $(VAR).o $(VAR)Test.o $(VAR).so $(SHAREDLIB)
DEPS := $(patsubst $(VAR).o:,,$(shell gcc -MM $(VAR).c -I$(IDIR)))
SHAREDLIB = $(subst \,,$(patsubst %.h,%.so,$(subst $(IDIR),$(LDIR), $(patsubst %$(VAR).h,,$(patsubst $(VAR).c,,$(DEPS))))))


.PHONY = all
.PHONY = run
.PHONY = mkdir
.PHONY = create_template_srcTest
.PHONY = open
.PHONY = cgdb
.PHONY = gitadd
.PHONY = debug
.PHONY = release
.PHONY = clean

all: mkdir $(VAR).out


$(VAR).out: $(OBJ)
	$(CC) $(CFLAGS) $(ODIR)$(VAR)Test.o $(LDIR)$(VAR).so -I$(IDIR) -o$(TARGET)


$(VAR).o: $(VAR).c
	$(CC) -c $(CFLAGS) -fPIC  $(LDFLAGS) $< -o$(ODIR)$@ -I$(IDIR)


$(VAR).so: $(VAR).o $(SHAREDLIB)
	$(CC) $(CFLAGS) -shared $(ODIR)$(VAR).o $(LDFLAGS) $(SHAREDLIB) -o $(LDIR)$@ -I$(IDIR)


$(VAR)Test.o: $(VAR)Test.c
	$(CC) -c $(CFLAGS) $(TDIR)$(VAR)Test.c -o$(ODIR)$@ -I$(IDIR)


$(SHAREDLIB):
#	$(shell echo $(subst lib,src,$(patsubst %.so,%,$(SHAREDLIB))) | xargs -n 1 cp -v makefile)
#	$(shell xargs -n 1 cp -v makefile<<<$(subst lib,src,$(patsubst %.so,%,$(SHAREDLIB))))
	$(subst lib,src,$(patsubst %.so,cd % && make;,$(SHAREDLIB)))

run: $(TARGET)
	$(TARGET)


print: 
	@echo $(DEPS)
	@echo $(SHAREDLIB)
	
mkdir:
	@ mkdir -p $(ODIR)
	@ mkdir -p $(BDIR)
	@ mkdir -p $(LDIR)
	
touch:
	touch $(VAR).c
	touch $(IDIR)/$(VAR).h
	touch $(TDIR)$(VAR)Test.c


create_template_srcTest:
	cp -n $(IDIR)/$(VAR).h $(VAR).c
	cp -n $(TDIR)templateTest.c $(TDIR)$(VAR)Test.c


open:
	gopen $(VAR).c
	gopen $(IDIR)/$(VAR).h
	gopen $(TDIR)$(VAR)Test.c


vlg:
	valgrind --leak-check=yes --track-origins=yes $(TARGET)
	

cgdb:
	cgdb $(TARGET)
	

gitadd:
	git add .
	git add ../../*$(VAR)*
	git status
		
	
debug: CFLAGS += -DEBUG
debug: all


release: CFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
release: all


clean:
	rm -f $(TARGET) $(ODIR)$(VAR)*.o $(BDIR)$(VAR)*.out $(LDIR)$(VAR).so
