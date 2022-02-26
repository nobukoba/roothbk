ROOT_VER_GTEQ_6 = $(shell expr `root-config --version|cut -f1 -d/` \>= 6.0)
ifeq ($(ROOT_VER_GTEQ_6),1)
#root version >= 6
ROOTCINT  = rootcling
else
# root version 5
ROOTCINT  = rootcint
endif

CXX        = g++
AR         = ar r
CXXFLAGS   = -g -I../../inc $(shell root-config --cflags) -fPIC
# If ROOT does not have TBufferJSON::FromJSON class, please use the below CXXFLAG
#CXXFLAGS   = -g -I../../inc $(shell root-config --cflags) -fPIC -DNoFromJSON
LFLAGS     = 
# CentOS 8
ROOTLIBS   = $(shell root-config --glibs) -lXMLIO -lRHTTP -lgfortran
# macOS 12.2
#ROOTLIBS   = $(shell root-config --glibs) -lXMLIO -lRHTTP -L /usr/local/lib/gcc/11/ -lgfortran
PACKLIB_A  = ../../lib/libminipacklib.a
PACKLIB_SO = -L../../lib  -lminipacklib
TARGETS    = libroothbklib.a libroothbklib.so

all:	$(TARGETS)

libroothbklib.a:  roothbklibDict.o hbkwrapper.o convertfunc.o
	$(AR) $@ $^
libroothbklib.so:  roothbklibDict.o hbkwrapper.o convertfunc.o $(PACKLIB_A)
	$(CXX) -shared $(LFLAGS) -o $@ $^ $(PACKLIB_A) -Wl,-rpath $(PWD) $(ROOTLIBS)
roothbklibDict.cxx: ../../inc/minicfortran.h ../../inc/hbkwrapper.h ../../inc/convertfunc.h ../../inc/roothbklibLinkDef.h
ifeq ($(ROOT_VER_GTEQ_6),1)
	$(ROOTCINT) -f $@ $^
else
	$(ROOTCINT) -f $@ -c $^
endif

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $<
.PHONY : clean
clean:
	rm -rf $(TARGETS) *.o *~ roothbklibDict*
