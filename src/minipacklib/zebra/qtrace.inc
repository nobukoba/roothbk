*     Nothing Nobu 2021.09.05
*
*#if !defined(CERNLIB_QTRHOLL)||defined(CERNLIB_A6M)
*      MQTRAC(NQTRAC+1) = NAMESR
*      NQTRAC = NQTRAC + 1
*      IF (NQTRAC.GE.41)      CALL ZFATAL
*#else
      MQTRAC(NQTRAC+1) = NAMESR(1)
      MQTRAC(NQTRAC+2) = NAMESR(2)
      NQTRAC = NQTRAC + 2
*      IF (NQTRAC.GE.41)      CALL ZFATAL
*#endif
