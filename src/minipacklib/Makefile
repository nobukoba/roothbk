TARGETS    = libminipacklib.so libminipacklib.a
CC        = gcc
FC        = gfortran
AR        = ar clq
CFLAGS    = -g -fPIC
FFLAGS    = -g -I../../inc -cpp -std=legacy -Wno-argument-mismatch -fPIC
LFLAGS    = 

OBJECTS	  = zebra.o hbook.o cernlib.o kernlib.o hlimap.o hidall.o mzwork.o hcreatem.o hshm.o hmapm.o hrin2.o hcopyu.o hcopyn.o hcopyt.o hbook1.o hbook2.o hbookb.o hbug.o hbin.o hbtit.o noarg.o intarg.o floarg.o hf1.o hf2.o hf1aut.o hfill.o hfilpf.o hfidp.o locatf.o hrout.o hmdir.o rzallo.o rzexpd.o rzmdir.o rzmods.o rzused.o icluns.o hloop.o hrzout.o fzotab.o rzout.o mzmark.o rzdelk.o rzpurf.o rzmake.o rzobkn.o rzwrt.o fzocv.o cfput.o hexist.o hcopy.o mzcopy.o hnoentput.o hpak.o hpake.o hbarx.o hbar2.o hfcx.o hfcxy.o hsifla.o hidopt.o zsorti.o hrdir.o hrdirm.o rzrdir.o

all:	$(TARGETS)
	cp -f $(TARGETS) ../../lib/

libminipacklib.so: $(OBJECTS)
	$(CXX) -shared $(LFLAGS) -o $@ $^
libminipacklib.a:  $(OBJECTS)
	echo $^ | xargs $(AR) $@

%.o: %.c
	$(CC)  $(CFLAGS)   -c $<
%.o: %.f
	$(FC)  $(FFLAGS)   -c $<
.PHONY : clean
clean:
	rm -rf $(TARGETS) *.o *~
