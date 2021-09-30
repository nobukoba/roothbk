      Program read_shm_f_so

      integer idvec(10000), imax
      integer id
      character*80 chtitl
      integer ncx,ncy,nwt,idb
      real xmin,xmax,ymin,ymax

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
      call hlimit(nwords)
      call hlimap(0,'EXAM')

      call hrin2(0,9999,0)
      call hidall(idvec,imax)
      call hdelet(0)
      
      do i = 1, imax
         id =idvec(i)
         call hrin2(id,999,0)
         if (quest(1).ne.0) then
            write(*,*) 'Error cannot read ID = ', id
            return
         endif
         call hdcofl()
         if (hcbits(1).ne.0) then
            call hgive(id,chtitl,ncx,xmin,xmax,ncy,ymin,ymax,nwt,idb)
            write(*,*) 'type: 1d'
            write(*,*) 'title: ', chtitl
            write(*,*) 'xbins:', ncx, ', xmin:', xmin, ', xmax:', xmax
         endif
         if ((hcbits(2).ne.0).or.(hcbits(3).ne.0)) then
            call hgive(id,chtitl,ncx,xmin,xmax,ncy,ymin,ymax,nwt,idb)
            write(*,*) 'type: 2d'
            write(*,*) 'title: ', chtitl
            write(*,*) 'xbins:', ncx, ', xmin:', xmin, ', xmax:', xmax
            write(*,*) 'xbins:', ncy, ', xmin:', ymin, ', ymax:', ymax
         endif
         call hdelet(id)
      enddo
      return

      end
