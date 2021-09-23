      program shm_read3
      parameter (nwpaw=10000)
      common/pawc/paw(nwpaw)
      common/zebq/lq(104)
      common/hcbook/hcbooki
      common/MZCC/mzcci
      
      integer idvec(1000000)
      integer noh
      write(*,*) 'loc(paw(1))/4', loc(paw(1))/4
      write(*,*) 'loc(lq(1))/4', loc(lq(1))/4
      write(*,*) 'loc(mzcci)/4', loc(mzcci)/4
      write(*,*) 'loc(hcbooki)/4', loc(hcbooki)/4
      write(*,*) 'loc(lq(1))/4-loc(paw(1))/4',loc(lq(1))/4-loc(paw(1))/4
      call hlimit(nwpaw)
      write(*,*) 'here'
      call hlimap(0,'TES7')
      
      call hrin(0,9999,0)
      call hidall(idvec,noh)
      
      do i = 1, noh
         id = idvec(i)
         call hprint(id)
         call hdelet(id)
      enddo
      
      end
