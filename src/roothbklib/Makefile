ROOT_VER_GTEQ_6_00 = $(shell expr `root-config --version|cut -f1 -d/` \>= 6.00)
ROOT_VER_GTEQ_6_14 = $(shell expr `root-config --version|cut -f1 -d/` \>= 6.14)
OS_TYPE            = $(shell uname -s)

TARGETS    = libroothbklib.a libroothbklib.so
CXX        = g++
AR         = ar r
ifeq ($(ROOT_VER_GTEQ_6_14),1)
CXXFLAGS   = -g -I../../inc $(shell root-config --cflags) -fPIC
else
CXXFLAGS   = -g -I../../inc $(shell root-config --cflags) -fPIC -DNoFromJSON
endif
LFLAGS     = 
ifeq ($(OS_TYPE),Darwin)
# macOS 12.2
LIBS       = -L /usr/local/lib/gcc/11/ -lgfortran
else
# Linux
LIBS       = -lgfortran
endif
ROOTLIBS   = $(shell root-config --glibs) -lXMLIO -lRHTTP
PACKLIB_A  = ../../lib/libminipacklib.a
ifeq ($(ROOT_VER_GTEQ_6_00),1)
#root version >= 6
ROOTCINT  = rootcling
else
# root version 5
ROOTCINT  = rootcint
endif

all:	$(TARGETS)

libroothbklib.a:  roothbklibDict.o hbkwrapper.o convertfunc.o
	$(AR) $@ $^
libroothbklib.so:  roothbklibDict.o hbkwrapper.o convertfunc.o $(PACKLIB_A)
	$(CXX) -shared $(LFLAGS) -o $@ $^ $(PACKLIB_A) $(ROOTLIBS) $(LIBS)
roothbklibDict.cxx: ../../inc/minicfortran.h ../../inc/hbkwrapper.h ../../inc/convertfunc.h ../../inc/roothbklibLinkDef.h
ifeq ($(ROOT_VER_GTEQ_6_00),1)
	$(ROOTCINT) -f $@ $^
else
	$(ROOTCINT) -f $@ -c $^
endif

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $<
.PHONY : clean
clean:
	rm -rf $(TARGETS) *.o *~ roothbklibDict*
