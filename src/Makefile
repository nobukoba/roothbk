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
	$(MAKE) clean -C minipacklib
	$(MAKE) clean -C roothbklib
	$(MAKE) clean -C exec
ifeq ($(ROOT_VER_GTEQ_6),1)
	rm -f ../lib/libminipacklib.so ../lib/libminipacklib.a ../lib/libroothbklib.so ../lib/libroothbklib.a ../lib/roothbklibDict_rdict.pcm
endif
	rm -f ../lib/libminipacklib.so ../lib/libminipacklib.a ../lib/libroothbklib.so ../lib/libroothbklib.a
