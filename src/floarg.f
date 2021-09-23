*
* $Id: floarg.F,v 1.1.1.1 1996/02/15 17:49:44 mclareni Exp $
*
* $Log: floarg.F,v $
* Revision 1.1.1.1  1996/02/15 17:49:44  mclareni
* Kernlib
*
*
*#include "kerngen/pilot.h"
*#if defined(CERNLIB_QMSUN)
*#include "sungs/floarg.F"
*#elif defined(CERNLIB_QMVAX)
*#include "vaxgs/floarg.F"
*#else
      FUNCTION FLOARG (ARGM)
C
C CERN PROGLIB# M250    FLOARG          .VERSION KERNFOR  4.23  891215
C ORIG. 01/8/82  ADAPTED FROM UFLINT
C
C
      DIMENSION    ARGM(9)
      EQUIVALENCE  (A,IA)
C
*#if defined(CERNLIB_QMCV64)
*      PARAMETER    (JEX=53, NEX=12, NEG=4095 )
*#endif
*#if defined(CERNLIB_QMCRY)
*      PARAMETER    (JEX=49, NEX=16, NEG=65535)
*#endif
*#if defined(CERNLIB_QMCDC)
*      PARAMETER    (JEX=49, NEX=12, NEG=4095 )
*#endif
*#if defined(CERNLIB_QMUNI)||defined(CERNLIB_QMUNO)
*      PARAMETER    (JEX=28, NEX= 9, NEG= 511 )
*#endif
*#if defined(CERNLIB_QMPDP)
*      PARAMETER    (JEX=28, NEX= 9, NEG= 511 )
*#endif
*#if defined(CERNLIB_QMDGE)||defined(CERNLIB_QMIBM)
*      PARAMETER    (JEX=25, NEX= 8, NEG= 255 )
*#endif
*#if (defined(CERNLIB_QIEEE))&&(defined(CERNLIB_B32))
      PARAMETER    (JEX=24, NEX= 9, NEG= 511 )
*#endif
*#if defined(CERNLIB_QMND3)
*      PARAMETER    (JEX=23, NEX=10, NEG=1023 )
*#endif
C
*#include "kerngen/q_jbit.inc"
*      JBIT(IZW,IZP)     = AND(ISHFTR(IZW,IZP-1),1)
*      JBYT(IZW,IZP,NZB) = ISHFTR(LSHIFT(IZW,65-IZP-NZB),64-NZB)

*     Ignoring t=pass
C
C
c     Nobu 20210905
      FLOARG = ARGM(1)
c     The following does not work for 64 bit float
c      A   = ARGM(1)
c      write(*,*) 'A, IA, ARGM(1)', A, IA, ARGM(1)
c      JCH = JBYT (IA,JEX,NEX)
c      IF (JCH.EQ.0)          GO TO 36
c      IF (JCH.EQ.NEG)        GO TO 36
c      FLOARG = A
c      RETURN
cC
c   36 FLOARG = IA
      RETURN
      END
*#endif
