ROOT_VER_GTEQ_6 = $(shell expr `root-config --version|cut -f1 -d/` \>= 6.0)
CURRDIR = $(PWD)

all:
	$(MAKE) -C minipacklib
	cp -f minipacklib/libminipacklib.so ../lib/
	cp -f minipacklib/libminipacklib.a ../lib/
	$(MAKE) -C roothbklib
	cp -f roothbklib/libroothbklib.so ../lib/
	cp -f roothbklib/libroothbklib.a ../lib/
ifeq ($(ROOT_VER_GTEQ_6),1)
	cp -f roothbklib/roothbklibDict_rdict.pcm ../lib/
endif
	$(MAKE) -C exec
clean:
	cd $(CURRDIR)/minipacklib; $(MAKE) clean
	cd $(CURRDIR)/roothbklib;  $(MAKE) clean
	cd $(CURRDIR)/exec;        $(MAKE) clean
	cd $(CURRDIR)/../lib;      rm *

