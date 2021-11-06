ROOT_VER_GTEQ_6 = $(shell expr `root-config --version|cut -f1 -d/` \>= 6.0)
CURRDIR = $(PWD)

all:
	make make_minipacklib
	make make_roothbklib
	make make_exec
make_minipacklib: minipacklib/libminipacklib.so minipacklib/libminipacklib.a
minipacklib/libminipacklib.so:
	cd minipacklib;  $(MAKE)
	cp -f minipacklib/libminipacklib.so ../lib/
	cp -f minipacklib/libminipacklib.a ../lib/
ifeq ($(ROOT_VER_GTEQ_6),1)
make_roothbklib: roothbklib/libroothbklib.so roothbklib/libroothbklib.a roothbklib/roothbklibDict_rdict.pcm
else
make_roothbklib: roothbklib/libroothbklib.so roothbklib/libroothbklib.a
endif
roothbklib/libroothbklib.so:
	cd $(CURRDIR)/roothbklib;  $(MAKE)
	cp -f roothbklib/libroothbklib.so ../lib/
	cp -f roothbklib/libroothbklib.a ../lib/
ifeq ($(ROOT_VER_GTEQ_6),1)
	cp -f roothbklib/roothbklibDict_rdict.pcm ../lib/
endif
make_exec:
	cd $(CURRDIR)/exec;        $(MAKE)

clean:
	cd $(CURRDIR)/minipacklib; $(MAKE) clean
	cd $(CURRDIR)/roothbklib;  $(MAKE) clean
	cd $(CURRDIR)/exec;        $(MAKE) clean
	cd $(CURRDIR)/../lib;      rm *

