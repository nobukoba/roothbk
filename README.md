# roothbk
Mini packlib spun off from the h2root.cxx source code in the CERN ROOT program


# Troubleshooting
### Another library including CERNlib is loaded
If another library including CERNlib (e.g., libAllGrutinizer.so) is loaded, you would see the follwoing message.
```
$ cd roothbk/lib/
$ ls 
libminipacklib.a  libminipacklib.so  libroothbklib.a  libroothbklib.so
$ root
...
root [0] gSystem->Load("libroothbklib.so")
(int)0
root [1] shm2dir("EXAM")
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
LOCB/LOCF: address 0x7f1547a7f360 exceeds the 32 bit address space
or is not in the data segments
This may result in program crash or incorrect results
Therefore we will stop here
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
```
This is a typical error when you use the normal (or DESY 64 bit) CERNlib in the 64-bit Linux. This message is written in a source file: cernlib_2005/2005/src/packlib/kernlib/kerngen/ccgen/lp64gs/chkloc.c. This message, however, is never written in my library (roothbk/minipacklib). So if you see this error, another cernlib is loaded.

### Compilation with old ROOTs (ROOT v6.1? or smaller)
You will see the following errors with old ROOTs.
```
make[1]: Entering directory '/home/kobayash/nobukoba/roothbk/src/roothbklib'
g++ -g -I../../inc -pthread -m64 -I/home/kobayash/cern/root_v5.34.38//include/root -fPIC -c convertfunc.cxx
convertfunc.cxx: In function 'void convert_dir_srv2hbk(int, TXMLEngine&, XMLNodePointer_t, Int_t, TString, TString, const char*, const char*)':
convertfunc.cxx:1109:20: error: 'FromJSON' is not a member of 'TBufferJSON'
       TBufferJSON::FromJSON(obj, result);
                    ^~~~~~~~
convertfunc.cxx: In function 'void convert_dir_srv2root(TXMLEngine&, XMLNodePointer_t, Int_t, TString, TString, TDirectory*)':
convertfunc.cxx:1209:20: error: 'FromJSON' is not a member of 'TBufferJSON'
       TBufferJSON::FromJSON(obj, result);
                    ^~~~~~~~
make[1]: *** [Makefile:39: convertfunc.o] Error 1
make[1]: Leaving directory '/home/kobayash/nobukoba/roothbk/src/roothbklib'
make: *** [Makefile:8: all] Error 2
```
This is because the TBufferJSON class is not implimented in old ROOTs. In order to solve the problem, CXXFLAG should be changed in src/roothbklib/Makefile as below.
```
#CXXFLAGS   = -g -I../../inc $(shell root-config --cflags) -fPIC
# If ROOT does not have TBufferJSON::FromJSON class, please use the below CXXFLAG
CXXFLAGS   = -g -I../../inc $(shell root-config --cflags) -fPIC -DNoFromJSON
```
