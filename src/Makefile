ROOT_VER_GTEQ_6 = $(shell expr `root-config --version|cut -f1 -d/` \>= 6.0)
CURRDIR = $(PWD)

all:
	$(MAKE) -C minipacklib
	cp -af minipacklib/libminipacklib.so ../lib/
	cp -af minipacklib/libminipacklib.a ../lib/
	$(MAKE) -C roothbklib
	cp -af roothbklib/libroothbklib.so ../lib/
	cp -af roothbklib/libroothbklib.a ../lib/
ifeq ($(ROOT_VER_GTEQ_6),1)
	cp -af roothbklib/roothbklibDict_rdict.pcm ../lib/
endif
	$(MAKE) -C exec
clean:
	cd $(CURRDIR)/minipacklib; $(MAKE) clean
	cd $(CURRDIR)/roothbklib;  $(MAKE) clean
	cd $(CURRDIR)/exec;        $(MAKE) clean
	cd $(CURRDIR)/../lib;      rm *

