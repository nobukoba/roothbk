ROOT_VER_GTEQ_6 = $(shell expr `root-config --version|cut -f1 -d/` \>= 6.0)
ifeq ($(ROOT_VER_GTEQ_6),1)
#root version >= 6
ROOTCINT  = rootcling
else
# root version 5
ROOTCINT  = rootcint
endif

CC        = gcc
CXX       = g++
FC        = gfortran
AR        = ar clq
CFLAGS    = -g -fPIC
CXXFLAGS  = -g $(shell root-config --cflags) -fPIC
FFLAGS    = -g -I. -cpp -std=legacy -Wno-argument-mismatch -fPIC
LFLAGS    = 
ROOTLIBS  = $(shell root-config --glibs) -lgfortran -lXMLIO -lRHTTP 

LIB       = librootminipacklib.so libroothbk.so libconvertfunc.so librootminipacklib.a libroothbk.a libconvertfunc.a
BIN       = shms2hbk shms2root shms2srv shm2hbk shm2root shm2srv hbk2shm hbk2root hbk2srv root2shm root2hbk root2srv srv2shm srv2hbk srv2root lshm dshm shm_monitor
OBJECTS	  = hlimap.o hidall.o mzwork.o hcreatem.o hshm.o hmapm.o hrin2.o hcopyu.o hcopyn.o hcopyt.o zebra.o hbook.o cernlib.o kernlib.o hbook1.o hbook2.o hbookb.o hbug.o hbin.o hbtit.o noarg.o intarg.o floarg.o hf1.o hf2.o hf1aut.o hfill.o hfilpf.o hfidp.o locatf.o hrout.o hmdir.o rzallo.o rzexpd.o rzmdir.o rzmods.o rzused.o icluns.o hloop.o hrzout.o fzotab.o rzout.o mzmark.o rzdelk.o rzpurf.o rzmake.o rzobkn.o rzwrt.o fzocv.o cfput.o hexist.o hcopy.o mzcopy.o hnoentput.o hpak.o hpake.o hbarx.o hbar2.o hfcx.o hfcxy.o hsifla.o hidopt.o zsorti.o hrdir.o hrdirm.o rzrdir.o

all:	$(LIB) $(BIN)

install: $(LIB) $(BIN)
	cp -f $(LIB) roothbkDict_rdict.pcm convertfuncDict_rdict.pcm ../lib/
	cp -f $(BIN) ../bin/

librootminipacklib.so: $(OBJECTS)
	$(CXX) -shared $(LFLAGS) -o $@ $^
librootminipacklib.a: $(OBJECTS)
	echo $^ | xargs $(AR) $@
libroothbk.so: roothbkDict.o roothbk.o $(OBJECTS)
	$(CXX) -shared $(LFLAGS) -o $@ $^ -Wl,-rpath $(PWD) $(ROOTLIBS)
libroothbk.a:  roothbkDict.o roothbk.o $(OBJECTS)
	echo $^ | xargs $(AR) $@
roothbkDict.cxx: cfortran.h roothbk.h roothbkLinkDef.h
ifeq ($(ROOT_VER_GTEQ_6),1)
	$(ROOTCINT) -f $@ $^
else
	$(ROOTCINT) -f $@ -c $^
endif
libconvertfunc.so: convertfuncDict.o convertfunc.o $(OBJECTS)
	$(CXX) -shared $(LFLAGS) -o $@ $^ -Wl,-rpath $(PWD) $(ROOTLIBS)
libconvertfunc.a: convertfuncDict.o convertfunc.o $(OBJECTS)
	echo $^ | xargs $(AR) $@
convertfuncDict.cxx: cfortran.h convertfunc.h convertfuncLinkDef.h
ifeq ($(ROOT_VER_GTEQ_6),1)
	$(ROOTCINT) -f $@ $^
else
	$(ROOTCINT) -f $@ -c $^
endif

shms2hbk:  % : %.o libconvertfunc.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
shms2root: % : %.o libconvertfunc.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran 
shms2srv:  % : %.o libconvertfunc.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
shm2hbk:   % : %.o libconvertfunc.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
shm2root:  % : %.o libconvertfunc.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
shm2srv:   % : %.o libconvertfunc.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
hbk2shm:   % : %.o libconvertfunc.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
hbk2root:  % : %.o libconvertfunc.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
hbk2srv:   % : %.o libconvertfunc.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
root2shm:  % : %.o libconvertfunc.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
root2hbk:  % : %.o libconvertfunc.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
root2srv:  % : %.o libconvertfunc.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
srv2shm:   % : %.o libconvertfunc.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
srv2hbk:   % : %.o libconvertfunc.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
srv2root:  % : %.o libconvertfunc.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
lshm:      % : %.o libconvertfunc.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
dshm:      % : %.o libconvertfunc.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
shm_monitor: % : %.o libconvertfunc.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $<
%.o: %.c
	$(CC)  $(CFLAGS)   -c $<
%.o: %.f
	$(FC)  $(FFLAGS)   -c $<
.PHONY : clean
clean:
	rm -rf $(LIB) $(BIN) *.o *~ roothbkDict* convertfuncDict*
