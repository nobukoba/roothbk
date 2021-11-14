*
* $id: fzocv.f,v 1.3 1999/06/18 13:29:30 couet exp $
*
* $log: fzocv.f,v $
* revision 1.3  1999/06/18 13:29:30  couet
* - qcardl.inc was empty: it is now removed and not used.
*   comment end cde removed.
*
* revision 1.2  1996/04/18 16:10:46  mclareni
* incorporate changes from j.zoll for version 3.77
*
* revision 1.1.1.1  1996/03/06 10:47:11  mclareni
* zebra
*
*
*#include "zebra/pilot.h"
*#if !defined(cernlib_fqxisn)
      subroutine fzocv (ms,mt)

c-    convert for output with copy
c-    from source in native to target in exchange data format

#include "zebra/quest.inc"
#include "zebra/mzioc.inc"
*
      dimension    ms(99), mt(99)

      double precision   thdb
      dimension    this(2)
      equivalence  (thdb,this)
      equivalence  (itha,tha,this(1)), (ithb,thb,this(2))

c----            conversion control in /mzioc/ :

c-    for a given call translation source ms -> target mt is done
c-        either  for a complete batch of nwfott words
c-                      if nwfodn==0  and  nwfoav>=nwfott

c-            or  for the first instalment of a batch of nwfott words
c-                      if nwfodn==0  and  nwfoav<nwfott

c-            or  for a new instalment of n=min(nwfoav,nwfott-nwfodn)
c-                      words, if  nwfodn/=0

c-    *  marks words to be initialized by the caller
c-       only for the call at the beginning of a new batch
c-
c-         nwfoav  number of words available in the buffer to receive
c-                                                         the result
c-                    set by the caller whenever a new lot of data
c-                    becomes available for conversion (new buffer)
c-                    counted down by fzocv
c-       * nwfott  total number of words in the batch to be done,
c-                    maybe in several instalments
c-       * nwfodn  number of words in the batch already done
c-                    set to zero by the caller at start of batch
c-                    (in fact mziocr sets it to zero)
c-         nwfore  n.w. remaining to be done for the pending batch
c-                    set by fzocv, zero if end of batch
c-
c-         ifocon  remembers the last conversion problem
c-            (1)  error code if -ve, expected type if +ve
c-            (2)  location of the word
c-            (3)  content  of the word

c-         mfosav
c-          (1+2)  saves type and word-count for re-entry

c-       * jfoend  position of last sector plus 1
c-       * jforep  position of repeat sector descr.
c-         jfocur  position of current sector description

c-   * mfo(jfo+1)  t= sector type as in format
c-   *        +2)  c= word count  as in format
c-                    c > 0 :  no. of words
c-                    c = 0 :  dynamic sector
c-                    c < 0 :  indefinite sector, rest of the bank

c-            jmt  # of words done so far for the current call
c-            jms  # of words done so far for the current batch

*#include "fzocvd1.inc"
*#include "fzocvd2.inc"

      jmt = 0
      if (nwfodn/=0) then
c--   re-entry to continue
         jmtex  = min (nwfore,nwfoav)
         jms    = nwfodn
         itype  = mfosav(1)
         nwsec  = mfosav(2)
      else         
         nwfore = nwfott
         jmtex  = min (nwfore,nwfoav)
         
         jms    = 0
         jfocur = 0
         ifocon(1) = 0
      endif

      do while (.true.)
         if (nwfodn==0) then
            igoto31 = 0
c------start next sector         
            itype  = mfo(jfocur+1)
            if (itype==7) then
c--   self-describing sector            
               iword = ms(jms+1)
               itype = mod (iword,16)
               nwsec = iword/16
            else
               nwsec = mfo(jfocur+2)
               if   (nwsec < 0) then
c--   rest of the bank
                  nwsec = nwfore
                  igoto31 = 1
               else if (nwsec == 0 ) then
c--   dynamic sector
                  iword = ms(jms+1)
                  nwsec = iword
               else
                  igoto31 = 1
               endif         
            endif
            
            if (igoto31 == 0) then
               mt(jmt+1) = iword
               jmt = jmt + 1
               jms = jms + 1
               nwfore = nwfore - 1
               
               if (itype>=8)  then
c--   faulty sector control word
                  ifocon(1) = -1
                  ifocon(2) = jms
                  ifocon(3) = iword
c--   rest of the bank is unused         
                  itype = 0
                  nwsec = nwfore
               endif
               if (nwsec==0) then
c--   rest of the bank is unused         
                  itype = 0
                  nwsec = nwfore
               endif
               if (nwsec<0) then
c--   faulty sector control word
                  ifocon(1) = -1
                  ifocon(2) = jms
                  ifocon(3) = iword
c--   rest of the bank is unused         
                  itype = 0
                  nwsec = nwfore
               endif
            endif
         endif
c------conversion loops
c     lable # 31 commented out by nobu
         nwdo   = min (nwsec,jmtex-jmt)
         if (nwdo/=0) then
            if ((itype<=0).or.(itype>7)) then
               call vzero (mt(jmt+1),nwdo)
               jms = jms + nwdo
               jmt = jmt + nwdo
            else if (itype == 4) then
c--   d - double precision
               ndpn   = (nwdo+1) / 2
               nwdodb =  ndpn * 2
*     #include "fzocvfd.inc"
*     nobu added -->
               do jl=1,ndpn
                  mt(jmt+1) = ms(jms+2)
                  mt(jmt+2) = ms(jms+1)
                  jmt = jmt + 2
                  jms = jms + 2
               enddo
*     --> nobu
               if (nwdodb/=nwdo) then
                  if ((nwdodb>nwsec).or.(nwdodb>nwfore)) then
                     jms = jms - 1
                     jmt = jmt - 1
                     ifocon(1) = -2
                     ifocon(2) = jms
                     ifocon(3) = nwdo
                  else
                     nwdo = nwdodb
                  endif
               endif
            else if (itype == 5) then
c--   h - hollerith
*     #include "fzocvfh.inc"
*     --> added nobu
               call vxinvc (ms(jms+1),mt(jmt+1),nwdo)
               jmt = jmt + nwdo
               jms = jms + nwdo
*     --> nobu
*     ignoring t=pass
            else if ((itype <= 3).or.(itype >=6) )then
c---- copy as is
*     #include "fzocvjf.inc"
*     #include "fzocvfai.inc"
*     nobu added -->
               call ucopy (ms(jms+1),mt(jmt+1),nwdo)
               jmt = jmt + nwdo
               jms = jms + nwdo
*     --> nobu
c------end of sector
            endif
c--   rest of the bank unused
c--   b - bit strings
c--   i - integers
*     #include "fzocvfi.inc"
*     ignoring t=pass
c--   f - floating
*     #include "fzocvff.inc"
*     ignoring t=pass
c--   error : odd number of double-precision words
         endif
         
         nwfore = nwfott - jms
         if (jmt>=jmtex) then
            exit
         endif
         jfocur = jfocur + 2
         if (jfocur<jfoend) then
            cycle
         endif
         jfocur = jforep
      enddo      
c--   data or buffer exhausted

      iquest(1) = jmt
      nwfoav = nwfoav - jmt
      if (nwfore==0)             return
      
c--   ready for re-entry
      
      nwfodn    = jms
      mfosav(1) = itype
      mfosav(2) = nwsec - nwdo
      return
      end
*#endif
