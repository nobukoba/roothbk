      program write_hbk_f_a
      
      integer ier
      real a, b
      integer icycle

      parameter(nwords=32000000)
      common/pawc/h(nwords)

      call printaddr()
      call hlimit(nwords)
      call hropen(10,'LUN10','write_hbk_f.hb','n',1024,ier)
      if (ier .ne. 0) then
         write(*,*) " Error on hropen was ", ier
         return
      endif
      
      call hbook1(1,"test1;aa;bb",100,-4.,4.,0.)
      call hcopy(1,2,"test2")
      call hcopy(1,3,"test3")
      call hbook2(4,"test4",30,-3.,3.,30,-3.,3.,0.)
      
      do i = 1, 10000000
         call rannor(a,b)
         call hf1(1,a,1.)
         call hf1(2,b,1.)
         call hf1(3,a*a+b*b,1.)
         call hf2(4,a,b,1.)
         call hf2(5,a+1.,b+1.,1.)
         if(mod(i,1000000).eq.0) then
            write(*,*) ' hserver in loop index ', i
         endif
      enddo        
      call hrout(0,icycle,' ')
      call hrend('LUN10')
      return
      end
