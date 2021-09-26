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
LFLAGS     = 
ROOTLIBS   = $(shell root-config --glibs) -lgfortran -lXMLIO -lRHTTP 
PACKLIB_A  = ../../lib/libminipacklib.a
PACKLIB_SO = -L../../lib  -lminipacklib

TARGETS    = ../../lib/libroothbklib.so ../../lib/libroothbklib.a ../../lib/roothbklibDict_rdict.pcm

all:	$(TARGETS)

../../lib/libroothbklib.a:  roothbklibDict.o hbkwrapper.o convertfunc.o
	$(AR) $@ $^
../../lib/libroothbklib.so:  roothbklibDict.o hbkwrapper.o convertfunc.o $(PACKLIB_A)
	$(CXX) -shared $(LFLAGS) -o $@ $^ $(PACKLIB_A) -Wl,-rpath $(PWD) $(ROOTLIBS)
../../lib/roothbklibDict_rdict.pcm:  roothbklibDict.o
	cp -f roothbklibDict_rdict.pcm $@
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
