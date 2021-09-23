      Program hserver
*#include "hbook/hcbook.inc"
*#include "hbook/hcunit.inc"
*#include "hbook/hcdire.inc"
*#include "hbook/hcmail.inc"
*#include "hbook/hcpiaf.inc"
      CHARACTER*16   TEXT
*     
*     HBOOK program creating a "shared memory" 
*     area called 'TEST'
*     Routine HLIMAP replaces HLIMIT.
*     NWORDS is the amount of space requested 
*     in the shared area.
*     
      parameter(nwords=32000000)
      common/pawc/h(nwords)
      common/quest/iquest(100)
      common/hcbits/ihcbits(37)
      common/hcbook/ihcbook(51)
      common/rzcl/irzcl(11)
      common/zebq/izebq(104)
      common/mzcc/imzcc(411)
      CHARACTER*16 CTITLE

      call hlimit(nwords)
      call hlimap(0,'TES1')
*      call hlimap(nwords,'TES1')
*      call hlimap(0,'TES6')

*      CALL HCDIR('//TES1/AC',' ')
      CALL HLDIR('//TES1',' ')
*      IGOFF=-LOCF(LQ(1))-ICHTOP(2)
*      write(*,*) 'IGOFF, LQ(IGOFF+1) ', IGOFF, LQ(IGOFF+1)
*      CALL nosubdir(ndir)
*      write(*,*) 'ndir', ndir
*      CALL tisubdir(1,CTITLE)
*      write(*,*) '1, CTITLE: ', CTITLE, ' prefix'
      
      
*      write(*,*) 'NCHTOP', NCHTOP
*      write(*,*) 'CHTOP(1) ', CHTOP(1)
*      write(*,*) 'CHTOP(2) ', CHTOP(2)
*      write(*,*) 'ICHTOP(1) ', ICHTOP(1)
*      write(*,*) 'ICHTOP(2) ', ICHTOP(2)
*      IGOFF=-LOCF(LQ(1))-ICHTOP(1)
*      write(*,*) 'IGOFF, LQ(IGOFF+1) ', IGOFF, LQ(IGOFF+1)
*      IGOFF=-LOCF(LQ(1))-ICHTOP(2)
*      write(*,*) 'IGOFF, LQ(IGOFF+1) ', IGOFF, LQ(IGOFF+1)
*      NW=LQ(IGOFF+1)
*      write(*,*) 'hserver NW', NW
*      KOF=LQ(IGOFF+2)
*      write(*,*) 'hserver KOF', KOF
*      ILAST=LQ(IGOFF+1+NW-1)
*      write(*,*) 'hserver ILAST', ILAST
*      JR1=ILAST-KOF
*      write(*,*) 'hserver  JR1', JR1
*      call UHTOC(LQ(IGOFF+JR1+1+8),4,TEXT,16)
*      write(*,*) 'hserver  TEXT: ', TEXT
*      JR1=LQ(IGOFF+JR1-1)-KOF
*      call UHTOC(LQ(IGOFF+JR1+1+8),4,TEXT,16)
*      write(*,*) 'hserver  TEXT: ', TEXT
*      JR1=LQ(IGOFF+JR1-1)-KOF
*      call UHTOC(LQ(IGOFF+JR1+1+8),4,TEXT,16)
*      write(*,*) 'hserver  TEXT: ', TEXT
*      JR1=LQ(IGOFF+JR1)-KOF
*      call UHTOC(LQ(IGOFF+JR1+1+8),4,TEXT,16)
*      write(*,*) 'hserver  TEXT: ', TEXT
      
*     write(*,*) 'CHTOP(1) ', CHTOP(1)
*      write(*,*) 'CHTOP(2) ', CHTOP(2)
*      write(*,*) 'ICHTOP(1) ', ICHTOP(1)
*      write(*,*) 'ICHTOP(2) ', ICHTOP(2)
*      IGOFF=-LOCF(LQ(1))-ICHTOP(1)
*      write(*,*) 'IGOFF, LQ(IGOFF+1) ', IGOFF, LQ(IGOFF+1)
*      IGOFF=-LOCF(LQ(1))-ICHTOP(2)
*      write(*,*) 'IGOFF, LQ(IGOFF+1) ', IGOFF, LQ(IGOFF+1)
     
*      call hbook1(1,'test1;aa;bb',100,-4.,4.,0.)
*      call hcopy(1,2,'test2')
*      call hcopy(1,3,'test3')
*      call hbook2(4,'test4',30,-3.,3.,30,-3.,3.,0.)
*      call hldir('//TES1/AA','T')
*     call hbook2(5,'test5;aa;bb',30,-3.,3.,30,-3.,3.,0.)
***
*      do 10 i=1,1000000000
*         call rannor(a,b)
*         write(*,*) 'a,b',a,b
*         call hf1(1,a,1.)
**         call hf1(2,b,1.)
**         call hf1(3,a**2+b**2,1.)
*         call hf2(4,a,b,1.)
**         call hf2(5,a+1.,b+1.,1.)
*
*         if(mod(i,100000).eq.0)
*     X   print *,' hserver in loop index ',i
*  10  continue
*
      end
