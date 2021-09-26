      program read_hbk_f_a

      integer ier, record_size
      integer idvec(10000), imax
      integer id
      character*80 chtitl
      integer ncx,ncy,nwt,idb
      real xmin,xmax,ymin,ymax
      
      parameter(nwords=32000000)
      common/pawc/h(nwords)
      common/quest/quest(100)
      common/hcbits/hcbits(37)
      
      call printaddr()
      call hlimit(nwords)
      record_size = 0
      call hropen(10,'LUN10','write_hbk_f.hb','x',record_size,ier)
      if (ier.ne.0)  then
         write(*,*) " Error on hropen was ", ier
         return
      endif

      call hrin2(0,9999,0)
      call hidall(idvec, imax)
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
      call hrend('LUN10')
      return

      end
