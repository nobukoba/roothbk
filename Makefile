TARGET    = librootminipacklib.so

ROOT_VER_GTEQ_6 = $(shell expr `root-config --version|cut -f1 -d/` \>= 6.0)
ifeq ($(ROOT_VER_GTEQ_6),1)
#root version >= 6
ROOTLIBS  = $(shell root-config --glibs) -lgfortran
ROOTCINT  = rootcling
else
# root version 5
ROOTLIBS  = -L$(shell root-config --libdir) -lCore -lCint -lRIO -lNet -lHist -lGraf -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic -lgfortran
ROOTCINT  = rootcint
endif

GCC_VER_GTEQ_5 = $(shell expr `gcc -dumpversion | cut -f1-2 -d.` \>= 5.0)
ifeq ($(GCC_VER_GTEQ_5),1)
PIEFLAGS  =  -O -no-pie
else
PIEFLAGS  =
endif

CC        = gcc $(PIEFLAGS)
CXX       = g++
FC        = gfortran $(PIEFLAGS)
CFLAGS    = -fPIC
CXXFLAGS  = $(shell root-config --cflags) -fPIC
FFLAGS    = -std=legacy -Wno-argument-mismatch -fPIC
LFLAGS    = 

all:	$(TARGET)

$(TARGET): rootminipacklibDict.o rootminipacklib.o hlimap.o hidall.o mzwork.o hcreatem.o hshm.o hmapm.o hrin2.o hcopyu.o hcopyn.o hcopyt.o zebra.o hbook.o cernlib.o kernlib.o
	$(CXX) -shared $(LFLAGS) -o $@ $^ $(ROOTLIBS)
rootminipacklibDict.cxx: rootminipacklib.h rootminipacklibLinkDef.h
ifeq ($(ROOT_VER_GTEQ_6),1)
	$(ROOTCINT) -f $@ $^ -rmf rootminipacklibDict.rootmap
else
	$(ROOTCINT) -f $@ -c $^
endif
%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $<
%.o: %.c
	$(CC)  $(CFLAGS)   -c $<
%.o: %.f
	$(FC)  $(FFLAGS)   -c $<
.PHONY : clean
clean:
	rm -rf $(TARGET) *.o *~ rootminipacklibDict* h2root_funcDict*
