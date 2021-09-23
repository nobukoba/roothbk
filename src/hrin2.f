* copied from root/misc/minicern/src/hbook.f
* 
*-------------------------------------------------------------------------------
*  c/o Nobu 2018/01/25 16:13:47
*      SUBROUTINE HRIN(IDD,ICYCLE,KOFSET)

      SUBROUTINE HRIN2(IDD,ICYCLE,KOFSET)
#include "hbook/hcntpar.inc"
#include "hbook/hntcur.inc"
#include "hbook/hcbook.inc"
#include "hbook/hcflag.inc"
#include "hbook/hcdire.inc"

      COMMON/QUEST/IQUEST(100)
      CHARACTER*128 CHWOLD
      INTEGER       KEYS(2)
      DATA KHIDE,KHID1,KHID2,KHCO1,KHCO2/4HHIDE,4HHID1,4HHID2,
     +                                   4hHCO1,4HHCO2/
      INTEGER*8 LOCQ, LOCF

      IOFSET=KOFSET

*      write(*,*) 'ICDIR ',ICDIR
*      write(*,*) 'ICHTOP(ICDIR) ',ICHTOP(ICDIR)
      IF(ICHTOP(ICDIR).LT.0)THEN
* c/o Nobu 2018/01/26 20:18:17 -->
*         print*, '>>>>>> HRIN: ICHTOP(ICDIR).LT.0'
* --> End
* Nobu added 2018/01/25 16:16:27 -->
         IF(INDEX(HFNAME(ICDIR),'memory').NE.0)THEN
            LOCQ=1-LOCF(IQUEST(1))-ICHTOP(ICDIR)
*            LOCQ=1-LOC(IQUEST(1))/4-ICHTOP(ICDIR)
            write(*,*) "LOCF(IQUEST(1)", LOCF(IQUEST(1))
            write(*,*) "IQUEST(1)", IQUEST(1)
            write(*,*) "LOC(IQUEST(1))", LOC(IQUEST(1))
            write(*,*) "ICHTOP(ICDIR)", ICHTOP(ICDIR)
            write(*,*) "ICDIR", ICDIR
            write(*,*) "LOCQ", LOCQ
            write(*,*) 'hrin2.f here 1'
            write(*,*) "IQUEST(LOCQ)", IQUEST(LOCQ)
            write(*,*) 'hrin2.f here 2'
            CALL HCOPYU(IDD,IQUEST(LOCQ),IOFSET)
            write(*,*) "here in hrin2 1"
*         ELSE
*            LOCQ=1-LOCF(IQUEST(1))-ICHTOP(ICDIR)
*            CALL HCOPYM(IDD,IQUEST(LOCQ),IOFSET)
         ENDIF
         CALL SBIT1(IQ(LCID),5)
         write(*,*) "IQUEST(LOCQ)", IQUEST(LOCQ)
         GO TO 80
* --> End
      ENDIF
      IF(ICYCLE.GT.1000.AND.IDD.EQ.0)THEN
         CALL HPAFF(CHCDIR,NLCDIR,CHWOLD)
         LQ(LHBOOK-NLPAT-10)=LCDIR
      ENDIF
      NRHIST=IQ(LCDIR+KNRH)
      IF(KOFSET.EQ.99999.AND.NRHIST.GT.0)THEN
         IF(IQ(LTAB+NRHIST).GE.KOFSET)IOFSET=IQ(LTAB+NRHIST)+1000000
      ENDIF
      KEYS(2) = 0
      IQ42=0
      IDN=IDD
      IF(IDD.EQ.0)THEN
         KEYS(1) = 1
         CALL HRZIN(IHDIV,0,0,KEYS,9999,'SC')
         IDN=IQUEST(21)
         IQ42=IQUEST(22)
      ENDIF
   10 ID=IDN+IOFSET
      NRHIST=IQ(LCDIR+KNRH)
      IDPOS=LOCATI(IQ(LTAB+1),NRHIST,ID)
      INMEM=0
      IF(IDPOS.GT.0)THEN
         LC=LQ(LTAB-IDPOS)
         IF(JBIT(IQ(LC),5).EQ.0)THEN
            INMEM=1
         ELSE
            print*, '+Already existing histogram replaced','HRIN',ID
            CALL HDELET(ID)
            NRHIST=IQ(LCDIR+KNRH)
            IDPOS=-IDPOS+1
         ENDIF
      ENDIF
      KEYS(1) = IDN
      KEYS(2) = IQ42
      CALL HRZIN(IHDIV,0,0,KEYS,ICYCLE,'NC')
      IF(IQUEST(1).NE.0)GO TO 70
      IQ40=IQUEST(40)
      IQ41=IQUEST(41)
      IQ42=IQUEST(42)
      NWORDS=IQUEST(12)
      IOPTA=JBIT(IQUEST(14),4)
      IF(IOPTA.NE.0)GO TO 60
      IF(INMEM.NE.0)GO TO 60
      CALL HSPACE(NWORDS+1000,'HRIN  ',IDD)
      IF(IERR.NE.0)                    GO TO 70
      IDPOS=-IDPOS+1
      IF(NRHIST.GE.IQ(LTAB-1))THEN
         CALL MZPUSH(IHDIV,LTAB,500,500,' ')
      ENDIF
      DO 20 I=NRHIST,IDPOS,-1
         IQ(LTAB+I+1)=IQ(LTAB+I)
         LQ(LTAB-I-1)=LQ(LTAB-I)
   20 CONTINUE
      IF(LIDS.EQ.0)THEN
         KEYS(1) = IDN
         CALL HRZIN(IHDIV,LCDIR,-2,KEYS,ICYCLE,'ND')
         IF(IQUEST(1).NE.0)THEN
            print*, 'Bad sequence for RZ','HRIN',IDN
            GO TO 70
         ENDIF
         LIDS=LQ(LCDIR-2)
         LCID=LIDS
      ELSE
         LLID=LQ(LCDIR-9)
         KEYS(1) = IDN
         CALL HRZIN(IHDIV,LLID,  0,KEYS,ICYCLE,'ND')
         IF(IQUEST(1).NE.0)THEN
            print*, 'Bad sequence for RZ','HRIN',IDN
            GO TO 70
         ENDIF
         LCID=LQ(LLID)
      ENDIF
      IQ(LCID-5)=ID
      LQ(LCDIR-9)=LCID
      IQ(LCDIR+KNRH)=IQ(LCDIR+KNRH)+1
      IQ(LTAB+IDPOS)=ID
      LQ(LTAB-IDPOS)=LCID
      CALL SBIT1(IQ(LCID),5)
      IF(JBIT(IQ(LCID+KBITS),1).NE.0)THEN
         IF(IQ(LCID-4).EQ.KHIDE)THEN
            IQ(LCID-4)=KHID1
            L=LQ(LCID-1)
            IF(L.NE.0)IQ(L-4)=KHCO1
         ENDIF
      ENDIF
      IF(JBYT(IQ(LCID+KBITS),2,2).NE.0)THEN
         IF(IQ(LCID-4).EQ.KHIDE)THEN
            IQ(LCID-4)=KHID2
            L=LQ(LCID-1)
            IF(L.NE.0)IQ(L-4)=KHCO2
         ENDIF
      ENDIF
      IF(JBIT(IQ(LCID+KBITS),4).NE.0)THEN
         IF (IQ(LCID-2) .EQ. 2) THEN
            NCHRZ=IQ(LCID+11)
            IF(NCHRZ.LE.0)GO TO 30
            ITAG1=IQ(LCID+10)
            NW=IQ(LCID-1)-ITAG1+1
            NPLUS=32-ITAG1
            IF(NPLUS.GT.0)THEN
               CALL MZPUSH(IHDIV,LCID,0,NPLUS,' ')
               CALL UCOPY2(IQ(LCID+ITAG1),IQ(LCID+32),NW)
               IQ(LCID+9)=IQ(LCID+9)+NPLUS
               IQ(LCID+10)=32
            ENDIF
            CALL HPAFF(CHCDIR,NLCDIR,CHWOLD)
            NCHRZ=LENOCC(CHWOLD)
            CALL UCTOH(CHWOLD,IQ(LCID+12),4,NCHRZ)
            IQ(LCID+11)=NCHRZ
   30       IQ(LCID)=9999
            LC=LQ(LCID-1)
            CALL SBIT0(IQ(LC),1)
            IF(NCHRZ.LE.0)THEN
               NMORE=IQ(LCID+5)+3-IQ(LCID-3)
               IF(NMORE.GT.0)THEN
                  CALL MZPUSH(IHDIV,LCID,NMORE,0,' ')
               ENDIF
               IF(IQ(LCID+5).GE.1)THEN
                  DO 40 IB=1,IQ(LCID+5)
                     LQ(LCID-3-IB)=LC
                     LC=LQ(LC)
                     IF(LC.EQ.0)THEN
                        LC=LQ(LCID-1)
                        GO TO 60
                     ENDIF
   40             CONTINUE
                  LC=LQ(LCID-1)
               ENDIF
            ELSE
               IF(ICHTOP(ICDIR).LT.1000) THEN
                  print*, '>>>>>> CALL HRZKEY(IDN)'
******            CALL HRZKEY(IDN)
               ENDIF
               IQ(LCID+5)=IDN
            ENDIF
            GO TO 60
         ELSE
            NCHRZ=IQ(LCID+ZNCHRZ)
            IF(NCHRZ.LE.0)GO TO 50
            ITIT1=IQ(LCID+ZITIT1)
            NW=IQ(LCID-1)-ITIT1+1
            NPLUS=34-ITIT1
            IF(NPLUS.GT.0)THEN
               CALL MZPUSH(IHDIV,LCID,0,NPLUS,' ')
               CALL UCOPY2(IQ(LCID+ITIT1),IQ(LCID+34),NW)
               IQ(LCID+ZITIT1)=34
            ENDIF
            CALL HPAFF(CHCDIR,NLCDIR,CHWOLD)
            NCHRZ=LENOCC(CHWOLD)
            CALL UCTOH(CHWOLD,IQ(LCID+ZNCHRZ+1),4,NCHRZ)
            IQ(LCID+ZNCHRZ)=NCHRZ
   50       IQ(LCID)=9999
            LC = LQ(LCID-1)
            CALL SBIT0(IQ(LC),1)
            CALL SBIT0(IQ(LC),2)
            CALL SBIT0(IQ(LC),3)
            CALL HNMSET(ID,ZIBANK,0)
            CALL HNMSET(ID,ZITMP,0)
            IQ(LCID+ZIFTMP) = 2
            IQ(LCID+ZID)    = IDN
            NTCUR = 0
            GO TO 60
         ENDIF
      ENDIF
   60 IF(IQ40.EQ.0)GO TO 80
      IDN=IQ41
      IF(IDD.EQ.0)GO TO 10
   70 CONTINUE
   80 RETURN
      END
