# roothbk
Utility to handle HBOOK and ROOT files.

# Highlight of the program
## Online analysis
At RCNP experiments, online histograms are stored in the shared memory by using the analyser Tamii-ana. A conventional way to show the histograms is to use PAW as below.
```
$ paw
...
PAW > glo TEST
PAW > hi/li
            1  test1   
            2  test2   
            3  test3   
            4  test4   
PAW > hi/pl 1
... Waiting accumulation of events ...
PAW > hi/pl 1
```
Similar things can be done in the ROOT by using the roothbk library.
```
$ root
...
root [0] gSystem->Load("<path to roothbk directory>/roothbk/lib/libroothbklib.so")
root [1] lshm()
----------- Shared Memory Segments --------
Name key        shmid      owner      perms      bytes      nattch     status
     0x00000000 262144     okabem     600        1769472    2          dest
...
TEST 0x54534554 22544459   kobayash   666        128000000  1
...
root [2] shm2dir("TEST")
root [3] .ls
 OBJ: TH1F	h1_test1	test1 : 0 at: 0x248c2e0
 OBJ: TH1F	h2_test2	test2 : 0 at: 0x248caf0
 OBJ: TH1F	h3_test3	test3 : 0 at: 0x28da8e0
 OBJ: TH2F	h4_test4	test4 : 0 at: 0x28db2c0
root [4] h1_test1->Draw()
... Waiting accumulation of events ...
root [5] shm2dir("TEST"); h1_test1->Draw()
... Waiting accumulation of events ...
root [6] shm2dir("TEST"); h1_test1->Draw()
```
In addition, the histograms stored in the shared memory can be dumped by using an executable shm2root as below.
```
$ <path to roothbk directory>/roothbk/bin/shm2root TEST
```
Then TEST.root is created. The file includes the contents of the shared memory TEST.

## Monitoring histograms stored in the shared memories via the THTTPserver: shm_monitor
Another usefull program is shm_monitor. This automatically converts histograms stored in the shared memory to ROOT histograms on the THTTPserver. The histograms are seen at http://localhost:port_number with a web browser. This command is suitable to show online histograms. The following is the usage etc.
```
Usage:   shm_monitor port [shm_name_list]
Example: shm_monitor 8080 TEST,FRED
shm_name_list:
    Should be separated by commas with no space.
    If an empty string "" is given, all shared 
    memories is read.
port:
    TCP port number of the THttpServer
```
N.B. On saho-a/saho-b, all ports are closed. Therefore, the THTTPserver runing at saho-a/saho-b is not accessible from outside of saho-a/saho-b.

# Requirements
- Linux (CentOS 8 etc.)
- gcc, g++, and gfortran (around version 8)
- ROOT version 5 or version 6

N.B. This program does not require the CERN Program Library (CERNlib)! The source codes of CERNLib are included in this source codes. On macOS 12.2.1, somes commands does not work, but some commands work. On macOS 12.2.1, the size of the shared memory should be enlarged by the following command.
```
sudo sysctl -w kern.sysv.shmmax=12582912
sudo sysctl -w kern.sysv.shmall=12582912
```

# How to compile it
```
$ git clone https://github.com/nobukoba/roothbk
$ cd roothbk/src
$ make
```

# Functions
## Libraries
The libraries are located in the roothbk/lib directory.
```
$ cd roothbk/lib
$ ls
libminipacklib.a  libminipacklib.so  libroothbklib.a  libroothbklib.so  roothbklibDict_rdict.pcm
```
### A library to handle HBOOK files in ROOT's prompt: libroothblib.so
libroothbklib.so is an usefull shared library to handle HBOOK files in prompt of ROOT's CINT. The following is how to load the library.
```
$ root
...
root[0] gSystem->Load("<path to roothbk directory>/roothbk/lib/libroothbklib.so")
```
After loading the libraray, you can use the following commands. The details are found in the section "Executables".
- lshm(): List the shared memory with key names
- dshm("shm_name_key"): Selete the shared memory by the key name
- dir2hbk("hbk_file_name"): Save contesnts of the current ROOT's directory into a HBOOK file
- dir2root("root_file_name"): Save contesnts of the current ROOT's directory into a ROOT file
- dir2shm("shm_name"): Save contents of the current ROOT's directory into a shared memory
- dir2srv(port): Show the contents of the current ROOT's directory on the THTTPserver
- hbk2dir("hbk_file_name"): Convert a HBOOK file to a current ROOT directory
- hbk2root("hbk_file_name","root_file_name"): Convert a HBOOK file to a ROOT file
- hbk2shm("hbk_file_name","shm_name"): Write contensts of a HBOOK file into the shared memory
- hbk2srv("hbk_file_name",port): Show contents of a HBOOK file on the THTTPserver
- root2dir("root_file_name"): Convert a ROOT file to a current ROOT directory
- root2hbk("root_file_name","hbk_file_name"): Convert a ROOT file to a HBOOK file
- root2shm("root_file_name","shm_name"): Write contents of a ROOT file into the shared memory
- root2srv("root_file_name",port): Show contents of a ROOT file on the THTTPserver
- shm2dir("shm_name"): Dump histograms of a shared memory into a current ROOT directory
- shm2hbk("shm_name","hbk_file_name"): Dump histograms of a shared memory into a HBOOK file
- shm2root("shm_name","root_file_name"): Dump histograms of a shared memory into a ROOT file
- shm2srv("shm_name",port): Show histograms of a shared memory on THTTPserver
- shms2dir("shm_name_list"): Dump histograms of all the shared memories into a cuurent ROOT directory
- shms2hbk("shm_name_list","hbk_file_name"): Dump histograms of all the shared memories into a HBOOK file
- shms2root("shm_name_list","root_file_name"): Dump histograms of all the shared memories into a ROOT file
- shms2srv("shm_name_list",port): Show histograms of all the shared memories on the THTTPserver
- srv2hbk("srv_url","hbk_file_name"): Download histograms on the THTTPserver into a HBOOK file
- srv2hbk("srv_url","root_file_name"): Download histograms on the THTTPserver into a ROOT file
- srv2shm("srv_url","shm_name"): Convert histograms on the THTTPserver into a shared memory

### Mini version of packlib: libminipacklib.so and libminipacklib.a
libminipacklib.so and libminipacklib.a are the mini version of the HBOOK library packlib in CERNlib. The original CERNlib can not be loaded from ROOT, because CERNlib does not support the shared library format (.so). In order to solve the problem, I modified the hlimap.f, hshm.c, hbook.f files etc. Then now you can creat the .so file including CERNlib subroutines. Core subroutines of HBOOK are included in libminipacklib.so and libminipacklib.a. For instance, the following subroutines are available.
```
hlimit
hlimap
hbook1
hbook2
hf1
hf2
hfill
hidall
hpak
hpake
hropen
hrin
hrend
hrout
hdelet
hrdir
hcdir
hmdir
etc...
```
So, if your program just uses the above subroutine, you can replace the original libpacklib.a with libminipacklib.a. For example in RCNP saho-a/saho-b, the Makefile can be changed as below.
```
CERNLIB = -L/usr/lib64/cernlib/2006/lib -Wl,-static -lpacklib -lkernlib -Wl,-dy
-->
CERNLIB = -L/<path to roothbk>/roothbk/lib -Wl,-static -lminipacklib -Wl,-dy
```
If you want to use the shared library libminipacklib.so, you can modifiy your Makefile as below.
```
CERNLIB = -L/<path to roothbk>/roothbk/lib -lminipacklib
```
Then, you should set LD_LIBRARY_PATH as below.
```
export LD_LIBRARY_PATH=/<path to roothbk>/roothbk/lib:$LD_LIBRARY_PATH
```
If you do not like to modify the LD_LIBRARY_PATH, you can add -rpath option in your Makefile.
```
CERNLIB = -L/<path to roothbk>/roothbk/lib -lminipacklib -Wl,--rpath=/<path to roothbk>/roothbk/lib
```

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
Usage:   dshm shm_name1 [shm_name...]
Example: dshm SHM1 SHM2
```
The following is the example.
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
### shm_monitor: Monitoring the contents of the shared memories on the THTTPserver
```
Usage:   shm_monitor port [shm_name_list]
Example: shm_monitor 8080 TEST,FRED
shm_name_list:
    Should be separated by commas with no space.
    If an empty string "" is given, all shared 
    memories is read.
port:
    TCP port number of the THttpServer
```
N.B. This command is similar with the shms2srv command. The shms2srv command converts shared memories only once. On the other hand, the shm_monitor command constantly converts shared memories every 300 ms. After executing this command, access http://localhost:port with a web browser. You can see the histograms in the shared memory. This command is suitable to show online histograms. This command is terminated by ctrl-c.

### hbk2root: Convert a HBOOK file to a ROOT file
```
Usage:   hbk2root hbk_file_name [root_file_name]
Example: hbk2root input.hb output.root
hbk_file_name:
    Name of an input HBOOK file
root_file_name:
    Name of an output ROOT file. If this value is not given,
    the name is created from the input file name. For example,
    if the input file name is filename.hb, the output is filename.root
```
N.B. This command is the same as the h2root command, but the error calculation is bug-fixed.

### hbk2shm: Write contensts of a HBOOK file into the shared memory
```
Usage:   hbk2shm hbk_file_name shm_name
Example: hbk2shm input.hb TEST
hbk_file_name:
    Name of input HBOOK file.
shm_name:
    Name of output shared memory
```

### hbk2srv: Show contents of a HBOOK file on the THTTPserver
```
Usage:   hbk2srv hbk_file_name [port]
Example: hbk2srv input.hb 8080
hbk_file_name:
    Name of an input HBOOK file name.
port:
    TCP port number of the THTTPserver. Default: 8080.
```
After executing this command, access http://localhost:port with a web browser. You can see the histograms in the HBOOK file. This command is terminated by ctrl-c.

### root2hbk: Convert a ROOT file to a HBOOK file
```
Usage:   root2hbk root_file_name hbk_file_name
Example: root2hbk input.root output.hb
root_file_name:
    Name of an output ROOT file.
hbk_file_name:
    Name of an input HBOOK file.  If this value is not given,
    the name is created from the input file name. For example,
    if the input file name is filename.root, the output is filename.hb
```

### root2shm: Write contents of a ROOT file into the shared memory
```
Usage:   root2shm root_file_name shm_name
Example: root2shm input.root TEST
root_file_name:
    Name of input ROOT file.
shm_name:
    Name of the shared memory.
```

### root2srv: Show contents of a ROOT file on the THTTPserver
```
Usage:   root2srv root_file_name [port]
Example: root2srv input.root 8080
root_file_name:
    Name of an input ROOT file name.
port:
    TCP port number of the THTTPserver. Default: 8080
```
After executing this command, access http://localhost:port with a web browser. You can see the histograms in the ROOT file. This command is terminated by ctrl-c.

### shm2hbk: Dump histograms of a shared memory into a HBOOK file
```
Usage:   shm2hbk shm_name [hbk_file_name]
Example: shm2hbk TEST out.hb
shm_name:
    Name of the shared memory
hbk_file_name:
    Name of an output HBOOK file. If this value is not given,
    the name is created from the shm_name. For example, if the
    shm_name is TEST, the output is TEST.hb
```

### shm2root: Dump histograms of a shared memory into a ROOT file
```
Usage:   shm2root shm_name [root_file_name]
Example: shm2root TEST out.root
shm_name:
    Name of the shared memory
root_file_name:
    Name of an output ROOT file. If this value is not given,
    the name is created from the shm_name. For example, if the
    shm_name is TEST, the output is TEST.root
```

### shm2root: Dump histograms of a shared memory into a ROOT file
```
Usage:   shm2root shm_name [root_file_name]
Example: shm2root TEST out.root
shm_name:
    Name of the shared memory
root_file_name:
    Name of an output ROOT file. If this value is not given,
    the name is created from the shm_name. For example, if the
    shm_name is TEST, the output is TEST.root
```
### shm2srv: Show histograms of a shared memory on THTTPserver
```
Usage:   shm2srv shm_name [port]
Example: shm2srv TEST 8080
shm_name:
    Name of the shared memory
port:
    TCP port number of the THTTPserver
```
After executing this command, access http://localhost:port with a web browser. You can see the histograms in the ROOT file. This command is terminated by ctrl-c.

### shms2hbk: Dump histograms of all the shared memories into a HBOOK file
```
Usage:   shms2hbk shm_name_list [hbk_file_name]
Example: shms2hbk TEST,FRED out.hb
shm_name_list:
    List of names of shared memories. Should be separated by
    commas with no space. If an empty string "" is given,
    all shared memories is read.
hbk_file_name:
    Name of the output HBOOK file. Default value = shms.hb.
```
### shms2root: Dump histograms of all the shared memories into a ROOT file
```
Usage:   shms2root shm_name_list [root_file_name]
Example: shms2root TEST,FRED out.root
shm_name_list:
    Should be separated by commas with no space.
    If an empty string "" is given, all shared 
    memories will be read.
root_file_name:
    Name of the output ROOT file. Default value = shms.root.
```
### shms2srv: Show histograms of all the shared memories on the THTTPserver
```
Usage:   shms2srv shm_name_list [port]
Example: shms2srv TEST,FRED 8080
shm_name_list:
    Should be separated by commas with no space.
    If an empty string "" is given, all shared 
    memories will be read.
port:
    TCP port number of the THTTPserver. Default: 8080.
```
After executing this command, access http://localhost:port with a web browser. You can see the histograms in the shared memories. This command is terminated by ctrl-c.

### srv2hbk: Download histograms on the THTTPserver into a HBOOK file
```
Usage:   srv2hbk srv_url [hbk_file_name]
Example: srv2hbk "http://localhost:8080/" output.hb
srv_url:
    URL where running the THttpServer
hbk_file_name:
    Name of an output HBOOK file name.
    Default value = http.hb
```
N.B.: This command is supported on newer version of ROOT, because this command uses TBufferJSON::FromJSON() function.

### srv2hbk: Download histograms on the THTTPserver into a ROOT file
```
Usage:   srv2hbk srv_url [root_file_name]
Example: srv2hbk "http://localhost:8080/" output.root
srv_url:
    URL where running the THttpServer
root_file_name:
    Name of an output ROOT file name.
    Default value = thttpserver.root
```

### srv2shm: Convert histograms on the THTTPserver into a shared memory
```
Usage:   srv2shm srv_url [shm_name]
Example: srv2shm "http://localhost:8080/" TEST
srv_url:
    URL where running the THttpServer
shm_name:
    Name of a shared memory.
    Default value = HTTP
```

# Troubleshooting
## Compilation with old ROOTs (ROOT v6.1? or smaller)
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
This is because the TBufferJSON::FromJSON function is not implimented in old ROOTs. In order to solve the problem, CXXFLAG should be changed in src/roothbklib/Makefile as below.
```
#CXXFLAGS   = -g -I../../inc $(shell root-config --cflags) -fPIC
# If ROOT does not have TBufferJSON::FromJSON class, please use the below CXXFLAG
CXXFLAGS   = -g -I../../inc $(shell root-config --cflags) -fPIC -DNoFromJSON
```

## Another library including CERNlib is loaded
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
