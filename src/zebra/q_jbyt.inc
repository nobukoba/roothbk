*      JBYT(IZW,IZP,NZB) = ISHFT(ISHFT(IZW,33-IZP-NZB),-(32-NZB))
* For -fdefault-integer-8 option of gfortran
      JBYT(IZW,IZP,NZB) = ISHFT(
     +     IAND(ISHFT(IZW,33-IZP-NZB),X'FFFFFFFF'),
     +     -(32-NZB))
