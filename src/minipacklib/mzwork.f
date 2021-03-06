*
* $Id: mzwork.F,v 1.3 1999/06/18 13:30:21 couet Exp $
*
* $Log: mzwork.F,v $
* Revision 1.3  1999/06/18 13:30:21  couet
* - qcardl.inc was empty: It is now removed and not used.
*   Comment END CDE removed.
*
* Revision 1.2  1996/04/18 16:12:10  mclareni
* Incorporate changes from J.Zoll for version 3.77
*
* Revision 1.1.1.1  1996/03/06 10:47:18  mclareni
* Zebra
*
*
*#include "zebra/pilot.h"
      SUBROUTINE MZWORK (IXSTOR,DFIRST,DLAST,IFLAGP)

C-    Allocate working space, user called

C-    IFLAG = -1  reset wsp empty
C-             0  new wsp
C-             1  vary both limits, keep common links
C-             2  vary  only DLAST  limit, keep links and common data
C-             3  reset only DFIRST limit, zero all links
C-             4  vary  only DFIRST limit, keep common links

#include "zebra/zmach.inc"
#include "zebra/zstate.inc"
#include "zebra/zunit.inc"
#include "zebra/zvfaut.inc"
#include "zebra/mqsys.inc"

      INTEGER      DFIRST(9), DLAST(9), IFLAGP(9)
* c/o Nobu see minicern/zebra.f and mzlink.F -->
*#if (defined(CERNLIB_QTRHOLL))&&(!defined(CERNLIB_A6M))
* --> c/o Nobu
      DIMENSION    NAMESR(2)
      DATA  NAMESR / 4HMZWO, 4HRK   /
* c/o Nobu see minicern/zebra.f and mzlink.F -->
*#endif
*#if (defined(CERNLIB_QTRHOLL))&&(defined(CERNLIB_A6M))
*      DATA  NAMESR / 6HMZWORK /
*#endif
*#if !defined(CERNLIB_QTRHOLL)
*      CHARACTER    NAMESR*8
*      PARAMETER   (NAMESR = 'MZWORK  ')
*#endif
* --> c/o Nobu


* c/o Nobu see minicern/zebra.f and rzfile.F -->
*#include "zebra/q_jbit.inc"
* --> c/o Nobu
* Added Nobu see minicern/zebra.f and rzfile -->
*      JBIT(IZW,IZP) = IAND(ISHFT(IZW,-(IZP-1)),1)
* --> Added Nobu
*#include "zebra/q_jbyt.inc"
*#include "zebra/q_locf.inc"
*      write(*,*) 'mzwork 1 NQOFFT(1+1)', NQOFFT(1+1)
*      write(*,*) 'mzwork 1 LQSTA(NQOFFT(1+1)+1)'
*      write(*,*) LQSTA(NQOFFT(1+1)+1)
*      write(*,*) 'mzwork 1 LQSTA(NQOFFT(1+1)+21)'
*      write(*,*) LQSTA(NQOFFT(1+1)+21)
      IFLAG = IFLAGP(1)
*      write(*,*) 'mzwork 1 IFLAG', IFLAG

*#include "zebra/qtrace.inc"
      MQTRAC(NQTRAC+1) = NAMESR(1)
      MQTRAC(NQTRAC+2) = NAMESR(2)
      NQTRAC = NQTRAC + 2
*      IF (NQTRAC.GE.41)      CALL ZFATAL
*#include "zebra/qstore.inc"
      IF (JBYT(IXSTOR,27,6).NE.JQSTOR)  CALL MZSDIV (IXSTOR,-7)

* c/o Nobu see minicern/zebra.f and mzlink.F -->
*#if defined(CERNLIB_QDEBUG)
*      IF (IQVSTA.NE.0)       CALL ZVAUTX
*#endif
* --> c/o Nobu

      IF (IFLAG.LT.0)              GO TO 61

      NEWL  = LOCF (DFIRST(1)) - (LQSTOR+1)
      NEWD  = LOCF (DLAST(1))  -  LQSTOR
* c/o Nobu see  minicern/zebra.f and mzlink.F -->
*#if defined(CERNLIB_APOLLO)
*      NEWL  = RSHFT (IADDR(DFIRST(1)),2) - (LQSTOR+1)
*      NEWD  = RSHFT (IADDR(DLAST(1)),2)  - LQSTOR
*#endif
* --> c/o Nobu
      IF (IFLAG.GE.5)              GO TO 91
      IF (IFLAG.GE.3)  NEWD = LQSTA(1) - 1
      IF (IFLAG.EQ.2)  NEWL = NQLINK

C----              Check valid parameters

*      write(*,*) 'mzwork 2 NEWL, NEWD, NQREF', NEWL, NEWD, NQREF
*      write(*,*) 'mzwork 2 LQEND(KQT+2)', LQEND(KQT+2)
c Nobu c/o 20210905 for 64 bit addressing
      IF (NEWL.LT.NQREF)           GO TO 92
      IF (NEWD.LT.NEWL)            GO TO 93
      IF (IFLAG.GE.3)              GO TO 31
      IF (NEWD.GE.LQEND(KQT+2))       GO TO 94

C--                Check garbage collection

      NQRESV = LQSTA(KQT+2) - NQMINR - NEWD
      IF (NQRESV.GT.0)             GO TO 31
      LQEND(KQT+1) = LQSTA(KQT+1)
      JQDIVI    = 2
      CALL MZRESV
      NQRESV = LQSTA(KQT+2) - NQMINR - NEWD
      CALL MZGAR1

C--                Clear new links

   31 LA = NQREF
      IF (IFLAG.EQ.1)  LA = NQLINK
      IF (IFLAG.EQ.2)  LA = NQLINK
      IF (IFLAG.EQ.4)  LA = NQLINK
      N  = NEWL - LA
      IF (N.GT.0)  CALL VZERO (LQ(KQS+LA+1),N)

C--                Clear new data words


* c/o Nobu see  minicern/zebra.f and mzlink.F -->
*#if defined(CERNLIB_QDEBUG)
* --> c/o Nobu
      IF (IFLAG.GE.3)              GO TO 71
      IF (JBYT(IQDBUG,4,2).EQ.0)   GO TO 71
      IF   (IFLAG.LT.2)  THEN
          LA = NEWL  + 1
        ELSE
          LA = LQSTA(KQT+1)
        ENDIF

      LE = NEWD
      IF (JBIT(IQDBUG,5).NE.0)  LE=LQSTA(KQT+2) - 1
      IF (LE.LT.LA)                GO TO 71

      DO 38  L=LA,LE
   38 LQ(KQS+L) = IQNIL + L
* c/o Nobu see  minicern/zebra.f and mzlink.F -->
*#endif
* --> c/o Nobu
      GO TO 71

C----              Reset empty working space

   61 NEWL = NQREF
      NEWD = NQREF
* c/o Nobu see  minicern/zebra.f and mzlink.F -->
*#if defined(CERNLIB_QDEBUG)
* --> c/o Nobu
      IF (IFLAG.LT.-1)             GO TO 91
* c/o Nobu see  minicern/zebra.f and mzlink.F -->
*#endif
* --> c/o Nobu

C----              Set new limits

   71 NQLINK  = NEWL
      IQTABV(KQT+5) = NQLINK
      IF (IFLAG.LT.3)  THEN
          LQSTA(KQT+1)  = NEWD + 1
          LQEND(KQT+1)  = NEWD + 1
        ENDIF
* c/o Nobu see  minicern/zebra.f and mzgar1.F -->
*#if defined(CERNLIB_QDEBPRI)
* --> c/o Nobu
      IF (NQLOGL.GE.2)
     + WRITE (IQLOG,9071) JQSTOR,IFLAG,NQLINK,NEWD
 9071 FORMAT (' MZWORK-  Store',I3,' Flag=',I2,' Last Link/Data',2I7)
* c/o Nobu see  minicern/zebra.f and mzgar1.F -->
*#endif
* --> c/o Nobu
*#include "zebra/qtrace99.inc"
  999 NQTRAC = NQTRAC - 2
*      write(*,*) 'mzwork * NQOFFT(1+1)', NQOFFT(1+1)
*      write(*,*) 'mzwork * LQSTA(NQOFFT(1+1)+1)'
*      write(*,*) LQSTA(NQOFFT(1+1)+1)
*      write(*,*) 'mzwork * LQSTA(NQOFFT(1+1)+21)'
*      write(*,*) LQSTA(NQOFFT(1+1)+21)

      RETURN

C------            Error conditions

   94 NQCASE = 1
   93 NQCASE = NQCASE + 1
   92 NQCASE = NQCASE + 1
   91 NQCASE = NQCASE + 1
      NQFATA = 4
      IQUEST(11) = NQREF
      IQUEST(12) = NEWL
      IQUEST(13) = NEWD
      IQUEST(14) = IFLAG
*#include "zebra/qtofatal.inc"
      IQUEST(9) = NAMESR(1)
      IQUEST(10)= NAMESR(2)
*      CALL ZFATAL
      END
