*
* $Id: intarg.F,v 1.1.1.1 1996/02/15 17:49:48 mclareni Exp $
*
* $Log: intarg.F,v $
* Revision 1.1.1.1  1996/02/15 17:49:48  mclareni
* Kernlib
*
*
*#include "kerngen/pilot.h"
*#if defined(CERNLIB_QMSUN)
*#include "sungs/intarg.F"
*#elif defined(CERNLIB_QMVAX)
*#include "vaxgs/intarg.F"
*#else
      FUNCTION INTARG (ARGM)
C
C CERN PROGLIB# M250    INTARG          .VERSION KERNFOR  4.23  891215
C ORIG. 01/8/82  ADAPTED FROM UFLINT
C
C
      DIMENSION    ARGM(9)
      EQUIVALENCE  (A,IA)
C
c#if defined(CERNLIB_QMCV64)
c      PARAMETER    (JEX=53, NEX=12, NEG=4095 )
c#endif
c#if defined(CERNLIB_QMCRY)
c      PARAMETER    (JEX=49, NEX=16, NEG=65535)
c#endif
c#if defined(CERNLIB_QMCDC)
c      PARAMETER    (JEX=49, NEX=12, NEG=4095 )
c#endif
c#if defined(CERNLIB_QMUNI)||defined(CERNLIB_QMUNO)
c      PARAMETER    (JEX=28, NEX= 9, NEG= 511 )
c#endif
c#if defined(CERNLIB_QMPDP)
c      PARAMETER    (JEX=28, NEX= 9, NEG= 511 )
c#endif
c#if defined(CERNLIB_QMDGE)||defined(CERNLIB_QMIBM)
c      PARAMETER    (JEX=25, NEX= 8, NEG= 255 )
c#endif
c#if (defined(CERNLIB_QIEEE))&&(defined(CERNLIB_B32))
      PARAMETER    (JEX=24, NEX= 9, NEG= 511 )
c#endif
c#if defined(CERNLIB_QMND3)
c      PARAMETER    (JEX=23, NEX=10, NEG=1023 )
c#endif
C
*#include "kerngen/q_jbit.inc"
*      JBIT(IZW,IZP)     = AND(ISHFTR(IZW,IZP-1),1)
*      JBYT(IZW,IZP,NZB) = ISHFTR(LSHIFT(IZW,65-IZP-NZB),64-NZB)

C     
C
c     Nobu 20210905
      A   = ARGM(1)
      INTARG = IA
c     The following may not work for 64 bit float
c      write(*,*) 'JEX, NEX, NEG'
c      write(*,*) JEX, NEX, NEG
c      A   = ARGM(1)
c      JCH = JBYT (IA,JEX,NEX)
c      IF (JCH.EQ.0)          GO TO 36
c      IF (JCH.EQ.NEG)        GO TO 36
c      INTARG = A
c      RETURN
cC
c   36 INTARG = IA
      RETURN
      END
*#endif
