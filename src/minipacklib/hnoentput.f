      SUBROUTINE HNOENTPUT(IDD,NUMB)
#include "hbook/hcbook.inc"
      COMMON /QUEST/ IQUEST(100)
      CALL HFIND(IDD,'HNOENT')
      IF(IQUEST(1).NE.0)THEN
         RETURN
      ELSE
         I4=JBIT(IQ(LCID+KBITS),4)
         write(*,*) 'hnoentput.f IQ(LCID+KBITS): ', IQ(LCID+KBITS)
         write(*,*) 'hnoentput.f LOC((LCID+KBITS)): ',
     &        LOC(IQ(LCID+KBITS))
         write(*,*) 'hnoentput.f IQ(LCID+KBITS): ',IQ(LCID+KBITS)
         write(*,*) 'hnoentput.f LOC(IQ(1)): ', LOC(IQ(1))
         write(*,*) 'hnoentput.f LCID: ', LCID
         write(*,*) 'hnoentput.f KBITS: ', KBITS
         write(*,*) 'hnoentput.f I4: ', I4
         IF(I4.NE.0)THEN
            IQ(LCID+3)=NUMB
            write(*,*) 'hnoentput.f NUMB: ', NUMB
         ELSE
            IQ(LCONT+KNOENT)=NUMB
            write(*,*) 'hnoentput.f LCONT: ', LCONT
            write(*,*) 'hnoentput.f KNOENT: ', KNOENT
            write(*,*) 'hnoentput.f IQ(LCONT+KNOENT): ',IQ(LCONT+KNOENT)
            write(*,*) 'hnoentput.f LOC(IQ(LCONT+KNOENT)): ',
     &           LOC(IQ(LCONT+KNOENT))
            
         ENDIF
      ENDIF
      END
      
