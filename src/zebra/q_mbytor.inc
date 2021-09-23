*      MBYTOR (MZ,IZW,IZP,NZB) = IOR (IZW,
*     + ISHFT (ISHFT(MZ,32-NZB),-(33-IZP-NZB)))
* For -fdefault-integer-8 option of gfortran
      MBYTOR (MZ,IZW,IZP,NZB) = IOR (IZW,
     + ISHFT (IAND(ISHFT(MZ,32-NZB),X'FFFFFFFF'),
     + -(33-IZP-NZB)))
