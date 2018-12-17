# Define compiler
CXX = g++

# Define flags. -D_VANILLA_ROOT_ is needed to avoid StMessMgr confusion
CFLAGS = $(shell root-config --cflags) -O0 -g -fPIC -Wall -pipe -std=c++11 -D_VANILLA_ROOT_ -D__ROOT__ -I.
LIBS = $(shell root-config --libs)
INCS = $(shell root-config --incdir)

# Define output library
STPICODST = libStHbtMaker.so

# Compile all *.cxx classes in the directory
SRC = $(shell find . -name "*.cxx")

all: $(STPICODST)

# $(SRC:.cc=.o) 
$(STPICODST): $(SRC:.cxx=.o) StHbtMaker_Dict.C
	$(CXX) $(CFLAGS) -shared $^ -o $(STPICODST) $(LIBS)

%.o: %.cxx
	$(CXX) -fPIC $(CFLAGS) -c -o $@ $<

StHbtMaker_Dict.C: $(shell find . -name "*.h" ! -name "*LinkDef*")
	rootcint -f $@ -c -D_VANILLA_ROOT_ -DROOT_CINT -D__ROOT__ -I. -I$(INCS) $^ StHbtMakerLinkDef.h

.PHONY: clean distclean

clean:
	rm -vf *.o StHbtMaker_Dict*

distclean:
	rm -vf *.o StHbtMaker_Dict* $(STPICODST)
