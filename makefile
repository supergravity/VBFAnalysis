LIBNAME = MYLIB

$(shell mkdir -p bin)
$(shell mkdir -p obj)
$(shell mkdir -p lib)

BACEPATH = $(shell pwd)
BOOST_PATH = /wk_cms/youying/boost_1_61_0

#--------------------------------------------------------------------------------------------

USEINCLUDE = -I $(BACEPATH)/interface
ROOTINCLUDE = $(shell root-config --cflags)
BOOSTINCLUDE = -I $(BOOST_PATH)

INCLUDE += $(USEINCLUDE)
INCLUDE += $(ROOTINCLUDE)
INCLUDE += $(BOOSTINCLUDE)

#-------------------------------------------------------------------------------------------

ROOTLIB = $(shell root-config --libs) 
ROOFITLIB = -lMinuit -lRooFit -lRooFitCore
BOOSTLIB = -L$(BOOST_PATH)/stage/lib -lboost_program_options
LIB += $(ROOTLIB)
LIB += $(ROOFITLIB)
LIB += $(BOOSTLIB)

#--------------------------------------------------------------------------------------------

LIBDIR = $(BACEPATH)/lib
EXEDIR = $(BACEPATH)/bin
OBJDIR = $(BACEPATH)/obj
TESTDIR = $(BACEPATH)/test
SRCDIR = $(BACEPATH)/src


OBJ_EXE=o
TEST_EXE=cpp
#--------------------------------------------------------------------------------------------

SRCS = $(wildcard $(BACEPATH)/src/*.cc)
EXES = $(wildcard $(BACEPATH)/test/*.cpp)
HEADER = $(wildcard $(BACEPATH)/interface/*.h)
OBJS = $(subst $(SRCDIR), $(OBJDIR),$(subst cc,$(OBJ_EXE),$(SRCS)))
BINS = $(subst $(TESTDIR), $(EXEDIR),$(subst .$(TEST_EXE),,$(EXES)))

#--------------------------------------------------------------------------------------------
CXXFLAGS=-g -m64 -O3 -Wall -Wl,-rpath=$(BACEPATH)/lib $(INCLUDE) -Wl,-rpath=$(BOOST_PATH)/stage/lib 
LIBS=-g -m64 $(LIB)
LDFLAGS = -shared -W


CXX=g++
LD=g++

.PHONY: all clean clear

all: $(BINS)


$(EXEDIR)/%:	$(TESTDIR)/%.cpp $(LIBDIR)/lib$(LIBNAME).so $(HEADER)
	$(CXX) -o $@ $(CXXFLAGS) $< $(LIBS) -L$(LIBDIR) -l$(LIBNAME) 

$(OBJDIR)/%.$(OBJ_EXE):		$(SRCDIR)/%.cc 
	$(CXX) -c $(CXXFLAGS) -fPIC $< -o $@

$(LIBDIR)/lib$(LIBNAME).so:	$(OBJS) 
	$(LD) $(LDFLAGS) -o $(LIBDIR)/lib$(LIBNAME).so $^ $(LIBS) 



clean:clear
clear:  
	rm -f $(OBJS) $(LIBDIR)/lib$(LIBNAME).so $(BINS) 
