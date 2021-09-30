FC        = gfortran
FFLAGS    = -g -cpp -I../../inc -std=legacy -Wno-argument-mismatch -fPIC
LFLAGS    = 
ROOTLIBS  = $(shell root-config --glibs) -lgfortran

TARGETS   = write_hbk_a write_hbk_so read_hbk_a read_hbk_so write_shm_a write_shm_so read_shm_a read_shm_so

all:	$(TARGETS)

write_hbk_a:  write_hbk_a.o
	$(FC) $(LFLAGS) -o $@ $^ ../../lib/libminipacklib.a -lgfortran
write_hbk_so: write_hbk_so.o
	$(FC) $(LFLAGS) -o $@ $^ -L../../lib -lroothbklib -lgfortran -Wl,-rpath,$(PWD)/../../lib
read_hbk_a:   read_hbk_a.o
	$(FC) $(LFLAGS) -o $@ $^ ../../lib/libminipacklib.a -lgfortran
read_hbk_so:  read_hbk_so.o
	$(FC) $(LFLAGS) -o $@ $^ -L../../lib -lroothbklib -lgfortran -Wl,-rpath,$(PWD)/../../lib
write_shm_a:  write_shm_a.o
	$(FC) $(LFLAGS) -o $@ $^ ../../lib/libminipacklib.a -lgfortran
write_shm_so: write_shm_so.o
	$(FC) $(LFLAGS) -o $@ $^ -L../../lib -lroothbklib -lgfortran -Wl,-rpath,$(PWD)/../../lib
read_shm_a:   read_shm_a.o
	$(FC) $(LFLAGS) -o $@ $^ ../../lib/libminipacklib.a -lgfortran
read_shm_so:  read_shm_so.o
	$(FC) $(LFLAGS) -o $@ $^ -L../../lib -lroothbklib -lgfortran -Wl,-rpath,$(PWD)/../../lib
%.o: %.f
	$(FC)  $(FFLAGS)   -c $<
.PHONY : clean
clean:
	rm -rf $(TARGETS) *.o *~
