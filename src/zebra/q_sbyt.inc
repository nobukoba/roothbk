*      MSBYT (MZ,IZW,IZP,NZB) = IOR (
*     + IAND (IZW, NOT(ISHFT (ISHFT(NOT(0),-(32-NZB)),IZP-1)))
*     + ,ISHFT (ISHFT(MZ,32-NZB), -(33-IZP-NZB)) )
* For -fdefault-integer-8 option of gfortran
      MSBYT (MZ,IZW,IZP,NZB) = IOR (
     + IAND (IZW, NOT(ISHFT (
     + ISHFT(X'FFFFFFFF',-(32-NZB)),IZP-1)))
     + ,ISHFT (IAND(ISHFT(MZ,32-NZB),X'FFFFFFFF'),
     + -(33-IZP-NZB)) )
