CXX       = g++
FC        = gfortran
CXXFLAGS  = -g  -I../inc $(shell root-config --cflags) -fPIC
FFLAGS    = -g -cpp -I../inc -std=legacy -Wno-argument-mismatch -fPIC
LFLAGS    = 
ROOTLIBS  = $(shell root-config --glibs) -lgfortran

TARGETS   = write_hbk_cxx_a write_hbk_cxx_so read_hbk_cxx_a read_hbk_cxx_so write_shm_cxx_a write_shm_cxx_so read_shm_cxx_a read_shm_cxx_so write_hbk_f_a write_hbk_f_so read_hbk_f_a read_hbk_f_so write_shm_f_a write_shm_f_so read_shm_f_a read_shm_f_so

all:	$(TARGETS)

write_hbk_cxx_a:  write_hbk_cxx.o
	$(CXX) $(LFLAGS) -o $@ $^ ../lib/libroothbklib.a ../lib/libminipacklib.a -lgfortran
write_hbk_cxx_so: write_hbk_cxx.o
	$(CXX) $(LFLAGS) -o $@ $^ -L../lib -lroothbklib -lgfortran -Wl,-rpath,$(PWD)/../lib
read_hbk_cxx_a:   read_hbk_cxx.o
	$(CXX) $(LFLAGS) -o $@ $^ ../lib/libroothbklib.a ../lib/libminipacklib.a -lgfortran
read_hbk_cxx_so:  read_hbk_cxx.o
	$(CXX) $(LFLAGS) -o $@ $^ -L../lib -lroothbklib -lgfortran -Wl,-rpath,$(PWD)/../lib
write_shm_cxx_a:  write_shm_cxx.o
	$(CXX) $(LFLAGS) -o $@ $^ ../lib/libroothbklib.a ../lib/libminipacklib.a -lgfortran
write_shm_cxx_so: write_shm_cxx.o
	$(CXX) $(LFLAGS) -o $@ $^ -L../lib -lroothbklib -lgfortran -Wl,-rpath,$(PWD)/../lib
read_shm_cxx_a:   read_shm_cxx.o
	$(CXX) $(LFLAGS) -o $@ $^ ../lib/libroothbklib.a ../lib/libminipacklib.a -lgfortran
read_shm_cxx_so:  read_shm_cxx.o
	$(CXX) $(LFLAGS) -o $@ $^ -L../lib -lroothbklib -lgfortran -Wl,-rpath,$(PWD)/../lib

write_hbk_f_a:  write_hbk_f_a.o
	$(CXX) $(LFLAGS) -o $@ $^ ../lib/libroothbklib.a ../lib/libminipacklib.a -lgfortran
write_hbk_f_so: write_hbk_f_so.o
	$(CXX) $(LFLAGS) -o $@ $^ -L../lib -lroothbklib -lgfortran -Wl,-rpath,$(PWD)/../lib
read_hbk_f_a:   read_hbk_f_a.o
	$(CXX) $(LFLAGS) -o $@ $^ ../lib/libroothbklib.a ../lib/libminipacklib.a -lgfortran
read_hbk_f_so:  read_hbk_f_so.o
	$(CXX) $(LFLAGS) -o $@ $^ -L../lib -lroothbklib -lgfortran -Wl,-rpath,$(PWD)/../lib
write_shm_f_a:  write_shm_f_a.o
	$(CXX) $(LFLAGS) -o $@ $^ ../lib/libroothbklib.a ../lib/libminipacklib.a -lgfortran
write_shm_f_so: write_shm_f_so.o
	$(CXX) $(LFLAGS) -o $@ $^ -L../lib -lroothbklib -lgfortran -Wl,-rpath,$(PWD)/../lib
read_shm_f_a:   read_shm_f_a.o
	$(CXX) $(LFLAGS) -o $@ $^ ../lib/libroothbklib.a ../lib/libminipacklib.a -lgfortran
read_shm_f_so:  read_shm_f_so.o
	$(CXX) $(LFLAGS) -o $@ $^ -L../lib -lroothbklib -lgfortran -Wl,-rpath,$(PWD)/../lib

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $<
%.o: %.f
	$(FC)  $(FFLAGS)   -c $<
.PHONY : clean
clean:
	rm -rf $(TARGETS) *.o *~
