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
CFLAGS    = -g -fPIC
CXXFLAGS  = -g  -I../src $(shell root-config --cflags) -fPIC
FFLAGS    = -g -cpp -I../src -std=legacy -Wno-argument-mismatch -fPIC
LFLAGS    = 
ROOTLIBS  = $(shell root-config --glibs) -lgfortran -lXMLIO -lRHTTP 

TARGET    = hbk_write hbk_write2 shm_read shm_read2 hserver hserver2 hserver3

all:	$(TARGET)

hbk_write: hbk_write.o
	$(CXX) $(LFLAGS) -o $@ $^ ../lib/librootminipacklib.a -lgfortran
hbk_write2: hbk_write.o
	$(CXX) $(LFLAGS) -o $@ hbk_write.o -L../lib -lrootminipacklib  -lgfortran -Wl,-rpath,$(PWD)/../lib
shm_read: shm_read.o
	$(CXX) $(LFLAGS) -o $@ $^ ../lib/librootminipacklib.a -lgfortran
shm_read2: shm_read.o
	$(CXX) $(LFLAGS) -o $@ shm_read.o -L../lib -lrootminipacklib  -lgfortran -Wl,-rpath,$(PWD)/../lib
shm_read3: shm_read3.o
	$(CXX) $(LFLAGS) -o $@ $^ -L/home/kobayash/cern/cernlib_2005_minipacklib_hbook_sandbox_double/2005/lib -lpacklib -lgfortran
hserver: hserver.o
	$(FC) $(LFLAGS) -o $@ $^ ../lib/librootminipacklib.a
hserver2: hserver.o
	$(FC) $(LFLAGS) -o $@ $^  -lgfortran -L/home/kobayash/cern/cernlib_2005_minipacklib_hbook_sandbox/2005/lib -lpacklib
hserver3: hserver.o
	$(CXX) $(LFLAGS) -o $@ hserver.o -L../lib -lrootminipacklib  -lgfortran -Wl,-rpath,$(PWD)/../lib

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $<
%.o: %.c
	$(CC)  $(CFLAGS)   -c $<
%.o: %.f
	$(FC)  $(FFLAGS)   -c $<
.PHONY : clean
clean:
	rm -rf $(TARGET) $(EXE) *.o *~
