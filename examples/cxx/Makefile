CXX       = g++
CXXFLAGS  = -g  -I../../inc $(shell root-config --cflags) -fPIC
LFLAGS    = 
ROOTLIBS  = $(shell root-config --glibs) -lgfortran

TARGETS   = write_hbk_a write_hbk_so read_hbk_a read_hbk_so write_shm_a write_shm_so read_shm_a read_shm_so

all:	$(TARGETS)

write_hbk_a:  write_hbk.o
	$(CXX) $(LFLAGS) -o $@ $^ ../../lib/libroothbklib.a ../../lib/libminipacklib.a -lgfortran
write_hbk_so: write_hbk.o
	$(CXX) $(LFLAGS) -o $@ $^ -L../../lib -lroothbklib -lgfortran -Wl,-rpath,$(PWD)/../../lib
read_hbk_a:   read_hbk.o
	$(CXX) $(LFLAGS) -o $@ $^ ../../lib/libroothbklib.a ../../lib/libminipacklib.a -lgfortran
read_hbk_so:  read_hbk.o
	$(CXX) $(LFLAGS) -o $@ $^ -L../../lib -lroothbklib -lgfortran -Wl,-rpath,$(PWD)/../../lib
write_shm_a:  write_shm.o
	$(CXX) $(LFLAGS) -o $@ $^ ../../lib/libroothbklib.a ../../lib/libminipacklib.a -lgfortran
write_shm_so: write_shm.o
	$(CXX) $(LFLAGS) -o $@ $^ -L../../lib -lroothbklib -lgfortran -Wl,-rpath,$(PWD)/../../lib
read_shm_a:   read_shm.o
	$(CXX) $(LFLAGS) -o $@ $^ ../../lib/libroothbklib.a ../../lib/libminipacklib.a -lgfortran
read_shm_so:  read_shm.o
	$(CXX) $(LFLAGS) -o $@ $^ -L../../lib -lroothbklib -lgfortran -Wl,-rpath,$(PWD)/../../lib

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $<
.PHONY : clean
clean:
	rm -rf $(TARGETS) *.o *~
