CXX       = g++
CXXFLAGS  = -g -I../../inc $(shell root-config --cflags) -fPIC
LFLAGS    = 
ROOTLIBS  = $(shell root-config --glibs) -lgfortran -lXMLIO -lRHTTP 

TARGETS   = ../../bin/shms2hbk ../../bin/shms2root ../../bin/shms2srv ../../bin/shm2hbk ../../bin/shm2root ../../bin/shm2srv ../../bin/hbk2shm ../../bin/hbk2root ../../bin/hbk2srv ../../bin/root2shm ../../bin/root2hbk ../../bin/root2srv ../../bin/srv2shm ../../bin/srv2hbk ../../bin/srv2root ../../bin/lshm ../../bin/dshm ../../bin/shm_monitor

all:	$(TARGETS)

../../bin/shms2hbk:  shms2hbk.o  ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
../../bin/shms2root: shms2root.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran 
../../bin/shms2srv:  shms2srv.o  ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
../../bin/shm2hbk:   shm2hbk.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
../../bin/shm2root:  shm2root.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
../../bin/shm2srv:   shm2srv.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
../../bin/hbk2shm:   hbk2shm.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
../../bin/hbk2root:  hbk2root.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
../../bin/hbk2srv:   hbk2srv.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
../../bin/root2shm:  root2shm.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
../../bin/root2hbk:  root2hbk.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
../../bin/root2srv:  root2srv.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
../../bin/srv2shm:   srv2shm.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
../../bin/srv2hbk:   srv2hbk.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
../../bin/srv2root:  srv2root.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
../../bin/lshm:      lshm.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
../../bin/dshm:      dshm.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
../../bin/shm_monitor: shm_monitor.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $<

.PHONY : clean
clean:
	rm -rf $(TARGETS) *.o *~
