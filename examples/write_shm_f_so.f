      program write_hbk_f_so
      real a, b

      parameter(nwords=32000000)
      common/pawc/h(nwords)
      common/quest/quest(100)
      common/hcbits/hcbits(37)
      common/hcbook/hcbook(51)
      common/rzcl/irzcl(11)
      common/zebq/izebq(104)
      common/mzcc/imzcc(411)
      common/bidon/ibidon(10006)
      common/mzcwk/imzcwk(5120)
      common/fzcx/ifzcx(71)
      
      call printaddr()
      call hlimap(32000000,'EXMF')
      call hbook1(1,'test1;aa;bb',100,-4.,4.,0.)
      call hcopy(1,2,'test2')
      call hcopy(1,3,'test3')
      call hbook2(4,'test4',30,-3.,3.,30,-3.,3.,0.)
      
      do i = 1, 10000000
         call rannor(a,b)
         call hf1(1,a,1.)
         call hf1(2,b,1.)
         call hf1(3,a*a+b*b,1.)
         call hf2(4,a,b,1.)
         call hf2(5,a+1.,b+1.,1.)
         if(mod(i,1000000).eq.0) then
            write(*,*) 'write_shm_f_so in loop index ', i
         endif
      enddo        
      return
      end
