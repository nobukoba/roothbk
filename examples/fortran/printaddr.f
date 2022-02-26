*-- Author :    Nobu Kobayashi         2021/09/25
      SUBROUTINE PRINTADDR()
      common/pawc/h(1)
      common/quest/iquest(100)
      common/hcbits/ihcbits(37)
      common/hcbook/ihcbook(51)
      common/rzcl/irzcl(11)
      common/zebq/izebq(104)
      common/mzcc/imzcc(411)
      common/bidon/ibidon(10006)
      common/mzcwk/imzcwk(5120)
      common/fzcx/ifzcx(71)
      common/fzci/ifzci(78)

      write(*,*) 'printaddr.f pawc:   ', LOC(h(1))
      write(*,*) 'printaddr.f quest:  ', LOC(iquest(1))
      write(*,*) 'printaddr.f hcbits: ', LOC(ihcbits(1))
      write(*,*) 'printaddr.f hcbook: ', LOC(ihcbook(1))
      write(*,*) 'printaddr.f rzcl: ',   LOC(irzcl(1))
      write(*,*) 'printaddr.f zebq: ',   LOC(izebq(1))
      write(*,*) 'printaddr.f mzcc: ',   LOC(imzcc(1))
      write(*,*) 'printaddr.f ibidon: ', LOC(ibidon(1))
      write(*,*) 'printaddr.f imzcwk: ', LOC(imzcwk(1))
      write(*,*) 'printaddr.f ifzcx: ',  LOC(ifzcx(1))
      write(*,*) 'printaddr.f ifzci: ',  LOC(ifzci(1))

      END


      





      
