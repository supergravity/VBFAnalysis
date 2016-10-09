BACKPATH=$(PWD)
EXES=$(wildcard $(BACKPATH)/*.cxx)
BINS=$(subst .cxx,,$(EXES))

CXXFLAGS=-g -m64 -O3 -Wall  $(shell root-config --cflags )
LIBS=-g -m64  $(shell root-config --libs)

CC:=g++

.PHONY: all clean clear

all: $(BINS)


$(BACKPATH)/% :    $(BACKPATH)/%.o
	$(CC) $< -o $@ $(LIBS)

$(BACKPATH)/%.o :	$(BACKPATH)/%.cxx 
	$(CC) -c $(CXXFLAGS) $< -o $@


clean:clear
clear:  
		rm -f $(BINS)
	
