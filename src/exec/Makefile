OS_TYPE            = $(shell uname -s)

CXX       = g++
CXXFLAGS  = -g -I../../inc $(shell root-config --cflags) -fPIC
LFLAGS    = 
ifeq ($(OS_TYPE),Darwin)
# macOS 12.2
LIBS       =  ../../lib/libroothbklib.a ../../lib/libminipacklib.a $(shell root-config --glibs) -lXMLIO -lRHTTP -L /usr/local/lib/gcc/11/ -lgfortran
else
# Linux
LIBS       =  ../../lib/libroothbklib.a ../../lib/libminipacklib.a $(shell root-config --glibs) -lXMLIO -lRHTTP -lgfortran
endif

TARGETS   = ../../bin/shms2hbk ../../bin/shms2root ../../bin/shms2srv ../../bin/shm2hbk ../../bin/shm2root ../../bin/shm2srv ../../bin/hbk2shm ../../bin/hbk2root ../../bin/hbk2srv ../../bin/root2shm ../../bin/root2hbk ../../bin/root2srv ../../bin/srv2shm ../../bin/srv2hbk ../../bin/srv2root ../../bin/lshm ../../bin/dshm ../../bin/shm_monitor

all:	$(TARGETS)

../../bin/shms2hbk:  shms2hbk.o
	$(CXX) $(LFLAGS) -o $@ $^ $(LIBS)
../../bin/shms2root: shms2root.o
	$(CXX) $(LFLAGS) -o $@ $^ $(LIBS) 
../../bin/shms2srv:  shms2srv.o
	$(CXX) $(LFLAGS) -o $@ $^ $(LIBS)
../../bin/shm2hbk:   shm2hbk.o
	$(CXX) $(LFLAGS) -o $@ $^ $(LIBS)
../../bin/shm2root:  shm2root.o
	$(CXX) $(LFLAGS) -o $@ $^ $(LIBS)
../../bin/shm2srv:   shm2srv.o
	$(CXX) $(LFLAGS) -o $@ $^ $(LIBS)
../../bin/hbk2shm:   hbk2shm.o
	$(CXX) $(LFLAGS) -o $@ $^ $(LIBS)
../../bin/hbk2root:  hbk2root.o
	$(CXX) $(LFLAGS) -o $@ $^ $(LIBS)
../../bin/hbk2srv:   hbk2srv.o
	$(CXX) $(LFLAGS) -o $@ $^ $(LIBS)
../../bin/root2shm:  root2shm.o
	$(CXX) $(LFLAGS) -o $@ $^ $(LIBS)
../../bin/root2hbk:  root2hbk.o
	$(CXX) $(LFLAGS) -o $@ $^ $(LIBS)
../../bin/root2srv:  root2srv.o
	$(CXX) $(LFLAGS) -o $@ $^ $(LIBS)
../../bin/srv2shm:   srv2shm.o
	$(CXX) $(LFLAGS) -o $@ $^ $(LIBS)
../../bin/srv2hbk:   srv2hbk.o
	$(CXX) $(LFLAGS) -o $@ $^ $(LIBS)
../../bin/srv2root:  srv2root.o
	$(CXX) $(LFLAGS) -o $@ $^ $(LIBS)
../../bin/lshm:      lshm.o
	$(CXX) -o $@ $^ $(LIBS) $(LFLAGS)
../../bin/dshm:      dshm.o
	$(CXX) -o $@ $^ $(LIBS) $(LFLAGS) 
../../bin/shm_monitor: shm_monitor.o
	$(CXX) $(LFLAGS) -o $@ $^ $(LIBS)

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $<

.PHONY : clean
clean:
	rm -rf $(TARGETS) *.o *~
