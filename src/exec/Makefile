CXX       = g++
CXXFLAGS  = -g -I../../inc $(shell root-config --cflags) -fPIC
LFLAGS    = 
ROOTLIBS  = $(shell root-config --glibs) -lgfortran -lXMLIO -lRHTTP 

TARGETS   = shms2hbk shms2root shms2srv shm2hbk shm2root shm2srv hbk2shm hbk2root hbk2srv root2shm root2hbk root2srv srv2shm srv2hbk srv2root lshm dshm shm_monitor

all:	$(TARGETS)
	cp -f $(TARGETS) ../../bin/

shms2hbk:  % : %.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
shms2root: % : %.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran 
shms2srv:  % : %.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
shm2hbk:   % : %.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
shm2root:  % : %.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
shm2srv:   % : %.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
hbk2shm:   % : %.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
hbk2root:  % : %.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
hbk2srv:   % : %.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
root2shm:  % : %.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
root2hbk:  % : %.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
root2srv:  % : %.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
srv2shm:   % : %.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
srv2hbk:   % : %.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
srv2root:  % : %.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
lshm:      % : %.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
dshm:      % : %.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran
shm_monitor: % : %.o ../../lib/libroothbklib.a ../../lib/libminipacklib.a
	$(CXX) $(LFLAGS) -o $@ $^ $(ROOTLIBS) -lgfortran

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $<

.PHONY : clean
clean:
	rm -rf $(TARGETS) *.o *~
