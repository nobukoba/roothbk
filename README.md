# roothbk
Mini packlib spun off from the h2root.cxx source code in the CERN ROOT

# How to compile
```
$ git clone https://github.com/nobukoba/roothbk
$ cd roothbk/src
$ make
```

# How to use it
## Executables
The executables are located in the roothbk/bin directory
```
$ cd roothbk/bin
$ ls
dshm      hbk2srv   root2shm  shm2root     shms2hbk   srv2hbk
hbk2root  lshm      root2srv  shm2srv      shms2root  srv2root
hbk2shm   root2hbk  shm2hbk   shm_monitor  shms2srv   srv2shm
```
### lshm: list the shared memory with key names
```
$ ./lshm
----------- Shared Memory Segments --------
Name key        shmid      owner      perms      bytes      nattch     status
     0x00000000 262144     okabem     600        1769472    2          dest
     0x00000000 22544385   kobaryo    600        1769472    2          dest
...
STAK 0x4b415453 2654261    stakasi    666        4000000    0
EXAM 0x4d415845 22544458   kobayash   666        128000000  1
```
### dshm: delete the shared memory by the key name
```
$ ./lshm
----------- Shared Memory Segments --------
Name key        shmid      owner      perms      bytes      nattch     status
...
EXAM 0x4d415845 22544458   kobayash   666        128000000  1

$ ./dshm EXAM
Executing the system command: ipcrm -M 0x4d415845
$ ./lshm
----------- Shared Memory Segments --------
Name key        shmid      owner      perms      bytes      nattch     status
...
```
### shm2root: Dump the contents of the shared memory in a ROOT file
```
$ ./shm2root EXAM
$ ls
... EXAM.root ...
```
or
```
$ ./shm2root EXAM out.root
$ ls
... out.root ...
```
### shms2root: Dump the contents of all the shared memories in a ROOT file
```
$ ./shms2root ""
$ ls
... shms.root ...
```

### hbk2root: convert a HBOOK file to a ROOT file
This is the same command as h2root, but the error calculation is bug-fixed properly.
```
$ ./hbk2root test.hb test.root
```

### root2hbk: convert a ROOT file to a HBOOK file
This is the same command as h2root, but the error calculation is bug-fixed properly.
```
$ ./hbk2root test.hb test.root
```

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
