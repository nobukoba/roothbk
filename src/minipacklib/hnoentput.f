      SUBROUTINE HNOENTPUT(IDD,NUMB)
#include "hbook/hcbook.inc"
      COMMON /QUEST/ IQUEST(100)
      CALL HFIND(IDD,'HNOENT')
      IF(IQUEST(1).NE.0)THEN
         RETURN
      ELSE
         I4=JBIT(IQ(LCID+KBITS),4)
         IF(I4.NE.0)THEN
            IQ(LCID+3)=NUMB
         ELSE
            IQ(LCONT+KNOENT)=NUMB
         ENDIF
      ENDIF
      END
