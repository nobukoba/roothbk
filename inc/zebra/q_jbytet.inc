*      JBYTET (MZ,IZW,IZP,NZB) = IAND (MZ,
*     + ISHFT (ISHFT(IZW,33-IZP-NZB),-(32-NZB)) )
* For -fdefault-integer-8 option of gfortran
      JBYTET (MZ,IZW,IZP,NZB) = IAND (MZ,
     + ISHFT (IAND(ISHFT(IZW,33-IZP-NZB),X'FFFFFFFF'),
     + -(32-NZB)) )
