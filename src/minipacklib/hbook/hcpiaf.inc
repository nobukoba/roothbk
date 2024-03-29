*     Nobu c/o all 2021.09.05
*
*     PARAMETER  (MXSLPF = 32)
*      COMMON/HCPIAF/NTPIAF
*     +             ,CONNPF,SERVPF,MASTPF,SLAVPF,CLINPF,CLUTPF,LOGLPF
*     +             ,NSLAVE,NSLBAD,NSLVPF,SLINPF(MXSLPF),SLUTPF(MXSLPF)
*     +             ,NGSIZE, MYSID, SMASK, SRIN, SROUT, SVMIO, STUSER
*     +             ,STCPU, MASPID
*      COMMON/HCPIA1/SLHOPF(MXSLPF), SLHBAD(MXSLPF), PIAFRC
**--- flag set by HGETNT if the current Ntuple is on Piaf server
*      LOGICAL NTPIAF
**--- flag if Piaf server is connected
*      LOGICAL CONNPF
**--- flag if this is a server (master or slave)
*      LOGICAL SERVPF
**--- flag if this is the master server
*      LOGICAL MASTPF
**--- flag if this is a slave server
*      LOGICAL SLAVPF
**--- sockets between client and master server
*      INTEGER CLINPF, CLUTPF
**--- log level of diagnostic output
*      INTEGER LOGLPF
**--- number of active slaves and mask used by the select (PSELCT) function
*      INTEGER NSLAVE, SMASK
**--- number of running slave servers and sockets between master and slaves
*      INTEGER NSLVPF, SLINPF, SLUTPF
**--- hosts on which slaves are running
*      CHARACTER*16 SLHOPF
**--- number hosts on which no slaves can be run
*      INTEGER NSLBAD
**--- hosts on which no slaves can be run
*      CHARACTER*16 SLHBAD
**--- current slave group view: group size and unique slave id
*      INTEGER NGSIZE, MYSID
**--- pid of the master server (used by slave servers)
*      INTEGER MASPID
**--- authentication record
*      CHARACTER*64 PIAFRC
**--- IO and CPU usage of all slaves
*      REAL SRIN, SROUT, SVMIO, STUSER, STCPU
**--- Work space
*      COMMON/HCPIAC/CHSMPF,    CHLMPF
*      CHARACTER     CHSMPF*80, CHLMPF*256
