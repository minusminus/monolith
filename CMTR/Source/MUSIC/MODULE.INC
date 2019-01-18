a_bpm      dw 2048
a_channels db 10
a_ptrn_restart dw offset a_patterns_table+00h
a_patterns_table dw offset a_pattern01
dw offset a_pattern01
dw offset a_pattern02
dw offset a_pattern02
dw offset a_pattern03
dw offset a_pattern03
dw offset a_pattern05
dw offset a_pattern04
dw offset a_pattern00
dw offset a_pattern00
dw offset a_pattern00
dw offset a_pattern00
dw offset a_pattern00
a_pattern00 db 03fh
     dw offset a_p00ch00
     dw offset a_p00ch01
     dw offset a_p00ch02
     dw offset a_p00ch03
     dw offset a_p00ch04
     dw offset a_p00ch05
     dw offset a_p00ch06
     dw offset a_p00ch07
     dw offset a_p00ch08
     dw offset a_p00ch09
a_pattern01 db 03fh
     dw offset a_p01ch00
     dw offset a_p01ch01
     dw offset a_p01ch02
     dw offset a_p01ch03
     dw offset a_p01ch04
     dw offset a_p01ch05
     dw offset a_p01ch06
     dw offset a_p01ch07
     dw offset a_p01ch08
     dw offset a_p01ch09
a_pattern02 db 03fh
     dw offset a_p02ch00
     dw offset a_p02ch01
     dw offset a_p02ch02
     dw offset a_p02ch03
     dw offset a_p02ch04
     dw offset a_p02ch05
     dw offset a_p02ch06
     dw offset a_p02ch07
     dw offset a_p02ch08
     dw offset a_p02ch09
a_pattern03 db 03fh
     dw offset a_p03ch00
     dw offset a_p03ch01
     dw offset a_p03ch02
     dw offset a_p03ch03
     dw offset a_p03ch04
     dw offset a_p03ch05
     dw offset a_p03ch06
     dw offset a_p03ch07
     dw offset a_p03ch08
     dw offset a_p03ch09
a_pattern04 db 03fh
     dw offset a_p04ch00
     dw offset a_p04ch01
     dw offset a_p04ch02
     dw offset a_p04ch03
     dw offset a_p04ch04
     dw offset a_p04ch05
     dw offset a_p04ch06
     dw offset a_p04ch07
     dw offset a_p04ch08
     dw offset a_p04ch09
a_pattern05 db 03fh
     dw offset a_p05ch00
     dw offset a_p05ch01
     dw offset a_p05ch02
     dw offset a_p05ch03
     dw offset a_p05ch04
     dw offset a_p05ch05
     dw offset a_p05ch06
     dw offset a_p05ch07
     dw offset a_p05ch08
     dw offset a_p05ch09
a_p00ch00   db 004h,001h
   db 081h
   db 044h
   db 087h
   db 043h
   db 080h
   db 043h
   db 080h
   db 044h
   db 081h
   db 044h
   db 087h
   db 043h
   db 080h
   db 043h
   db 080h
   db 044h
   db 081h
   db 044h
   db 087h
   db 043h
   db 080h
   db 043h
   db 080h
   db 044h
   db 080h
   db 044h
   db 080h
   db 044h
   db 080h
   db 044h
   db 080h
   db 044h
   db 044h
   db 044h
   db 044h
   db 044h
   db 044h
   db 044h
   db 044h
a_p00ch01   db 0bfh
a_p00ch02   db 0bfh
a_p00ch03   db 0bfh
a_p00ch04   db 0bfh
a_p00ch05   db 0bfh
a_p00ch06   db 02ch,001h
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
a_p00ch07   db 082h
   db 008h,001h
   db 044h
   db 086h
   db 044h
   db 080h
   db 048h
   db 083h
   db 048h
   db 044h
   db 048h
   db 085h
   db 044h
   db 048h
   db 080h
   db 048h
   db 082h
   db 048h
   db 044h
   db 086h
   db 044h
   db 080h
   db 048h
   db 083h
   db 048h
   db 044h
   db 048h
   db 085h
   db 044h
   db 048h
   db 080h
   db 048h
a_p00ch08   db 019h,001h
   db 06ch
   db 04dh
   db 082h
   db 04dh
   db 060h
   db 078h
   db 080h
   db 04dh
   db 060h
   db 081h
   db 04dh
   db 080h
   db 059h
   db 06ch
   db 04dh
   db 082h
   db 04dh
   db 060h
   db 078h
   db 080h
   db 04dh
   db 060h
   db 081h
   db 04dh
   db 080h
   db 059h
   db 06ch
   db 04dh
   db 082h
   db 04dh
   db 060h
   db 078h
   db 080h
   db 04dh
   db 060h
   db 081h
   db 04dh
   db 080h
   db 059h
   db 06ch
   db 04dh
   db 082h
   db 04dh
   db 060h
   db 078h
   db 080h
   db 04dh
   db 060h
   db 081h
   db 04dh
   db 080h
a_p00ch09   db 0bfh
a_p01ch00   db 0bfh
a_p01ch01   db 0bfh
a_p01ch02   db 0bfh
a_p01ch03   db 0bfh
a_p01ch04   db 0bfh
a_p01ch05   db 0bfh
a_p01ch06   db 0bfh
a_p01ch07   db 083h
   db 004h,001h
   db 086h
   db 044h
   db 086h
   db 044h
   db 086h
   db 044h
   db 086h
   db 044h
   db 086h
   db 044h
   db 086h
   db 044h
   db 086h
   db 044h
   db 082h
a_p01ch08   db 081h
   db 00dh,001h
   db 082h
   db 04dh
   db 080h
   db 078h
   db 080h
   db 04dh
   db 060h
   db 081h
   db 04dh
   db 082h
   db 04dh
   db 082h
   db 04dh
   db 080h
   db 078h
   db 080h
   db 04dh
   db 060h
   db 081h
   db 04dh
   db 082h
   db 04dh
   db 082h
   db 04dh
   db 080h
   db 078h
   db 080h
   db 04dh
   db 060h
   db 081h
   db 04dh
   db 082h
   db 04dh
   db 082h
   db 04dh
   db 080h
   db 078h
   db 080h
   db 04dh
   db 060h
   db 081h
   db 04dh
   db 080h
a_p01ch09   db 0bfh
a_p02ch00   db 0bfh
a_p02ch01   db 0bfh
a_p02ch02   db 0bfh
a_p02ch03   db 0bfh
a_p02ch04   db 0bfh
a_p02ch05   db 0bfh
a_p02ch06   db 02ch,001h
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
   db 06ch
   db 082h
a_p02ch07   db 083h
   db 004h,001h
   db 086h
   db 044h
   db 086h
   db 044h
   db 086h
   db 044h
   db 086h
   db 044h
   db 086h
   db 044h
   db 086h
   db 044h
   db 086h
   db 044h
   db 082h
a_p02ch08   db 081h
   db 00dh,001h
   db 082h
   db 04dh
   db 080h
   db 078h
   db 080h
   db 04dh
   db 060h
   db 081h
   db 04dh
   db 082h
   db 04dh
   db 082h
   db 04dh
   db 080h
   db 078h
   db 080h
   db 04dh
   db 060h
   db 081h
   db 04dh
   db 082h
   db 04dh
   db 082h
   db 04dh
   db 080h
   db 078h
   db 080h
   db 04dh
   db 060h
   db 081h
   db 04dh
   db 082h
   db 04dh
   db 082h
   db 04dh
   db 080h
   db 078h
   db 080h
   db 04dh
   db 060h
   db 081h
   db 04dh
   db 080h
a_p02ch09   db 0bfh
a_p03ch00   db 004h,001h
   db 081h
   db 044h
   db 087h
   db 043h
   db 080h
   db 043h
   db 080h
   db 044h
   db 081h
   db 044h
   db 087h
   db 043h
   db 080h
   db 043h
   db 080h
   db 044h
   db 081h
   db 044h
   db 087h
   db 043h
   db 080h
   db 043h
   db 080h
   db 044h
   db 080h
   db 044h
   db 080h
   db 044h
   db 080h
   db 044h
   db 080h
   db 044h
   db 044h
   db 044h
   db 044h
   db 044h
   db 044h
   db 044h
   db 044h
a_p03ch01   db 0bfh
a_p03ch02   db 0bfh
a_p03ch03   db 0bfh
a_p03ch04   db 0bfh
a_p03ch05   db 0bfh
a_p03ch06   db 0bfh
a_p03ch07   db 083h
   db 004h,001h
   db 086h
   db 044h
   db 086h
   db 044h
   db 086h
   db 044h
   db 086h
   db 044h
   db 086h
   db 044h
   db 086h
   db 044h
   db 086h
   db 044h
   db 082h
a_p03ch08   db 081h
   db 00dh,001h
   db 082h
   db 04dh
   db 080h
   db 078h
   db 080h
   db 04dh
   db 060h
   db 081h
   db 04dh
   db 082h
   db 04dh
   db 082h
   db 04dh
   db 080h
   db 078h
   db 080h
   db 04dh
   db 060h
   db 081h
   db 04dh
   db 082h
   db 04dh
   db 082h
   db 04dh
   db 080h
   db 078h
   db 080h
   db 04dh
   db 060h
   db 081h
   db 04dh
   db 082h
   db 04dh
   db 082h
   db 04dh
   db 080h
   db 078h
   db 080h
   db 04dh
   db 060h
   db 081h
   db 04dh
   db 080h
a_p03ch09   db 0bfh
a_p04ch00   db 004h,001h
   db 081h
   db 044h
   db 087h
   db 043h
   db 080h
   db 043h
   db 080h
   db 044h
   db 081h
   db 044h
   db 087h
   db 043h
   db 080h
   db 043h
   db 080h
   db 044h
   db 081h
   db 044h
   db 087h
   db 043h
   db 080h
   db 043h
   db 080h
   db 044h
   db 080h
   db 044h
   db 080h
   db 044h
   db 080h
   db 044h
   db 080h
   db 044h
   db 044h
   db 044h
   db 044h
   db 044h
   db 044h
   db 044h
   db 044h
a_p04ch01   db 0bfh
a_p04ch02   db 0bfh
a_p04ch03   db 0bfh
a_p04ch04   db 0bfh
a_p04ch05   db 0bfh
a_p04ch06   db 0afh
   db 02ch,001h
   db 080h
   db 06ch
   db 080h
   db 06ch
   db 080h
   db 06ch
   db 080h
   db 06ch
   db 080h
   db 06ch
   db 080h
   db 06ch
   db 080h
   db 06ch
   db 080h
a_p04ch07   db 082h
   db 008h,001h
   db 044h
   db 086h
   db 044h
   db 080h
   db 048h
   db 083h
   db 048h
   db 044h
   db 048h
   db 085h
   db 044h
   db 048h
   db 080h
   db 048h
   db 082h
   db 048h
   db 044h
   db 086h
   db 044h
   db 080h
   db 048h
   db 083h
   db 048h
   db 044h
   db 048h
   db 085h
   db 044h
   db 048h
   db 080h
   db 048h
a_p04ch08   db 019h,001h
   db 06ch
   db 04dh
   db 082h
   db 04dh
   db 060h
   db 078h
   db 080h
   db 04dh
   db 060h
   db 081h
   db 04dh
   db 080h
   db 059h
   db 06ch
   db 04dh
   db 082h
   db 04dh
   db 060h
   db 078h
   db 080h
   db 04dh
   db 060h
   db 081h
   db 04dh
   db 080h
   db 059h
   db 06ch
   db 04dh
   db 082h
   db 04dh
   db 060h
   db 078h
   db 080h
   db 04dh
   db 060h
   db 081h
   db 04dh
   db 080h
   db 059h
   db 06ch
   db 04dh
   db 082h
   db 04dh
   db 060h
   db 078h
   db 080h
   db 04dh
   db 060h
   db 081h
   db 04dh
   db 080h
a_p04ch09   db 0bfh
a_p05ch00   db 004h,001h
   db 081h
   db 044h
   db 087h
   db 043h
   db 080h
   db 043h
   db 080h
   db 044h
   db 081h
   db 044h
   db 087h
   db 043h
   db 080h
   db 043h
   db 080h
   db 044h
   db 081h
   db 044h
   db 087h
   db 043h
   db 080h
   db 043h
   db 080h
   db 044h
   db 080h
   db 044h
   db 080h
   db 044h
   db 080h
   db 044h
   db 080h
   db 044h
   db 044h
   db 044h
   db 044h
   db 044h
   db 044h
   db 044h
   db 044h
a_p05ch01   db 0bfh
a_p05ch02   db 0bfh
a_p05ch03   db 0bfh
a_p05ch04   db 0bfh
a_p05ch05   db 0bfh
a_p05ch06   db 0bfh
a_p05ch07   db 082h
   db 008h,001h
   db 044h
   db 086h
   db 044h
   db 080h
   db 048h
   db 083h
   db 048h
   db 044h
   db 048h
   db 085h
   db 044h
   db 048h
   db 080h
   db 048h
   db 082h
   db 048h
   db 044h
   db 086h
   db 044h
   db 080h
   db 048h
   db 083h
   db 048h
   db 044h
   db 048h
   db 085h
   db 044h
   db 048h
   db 080h
   db 048h
a_p05ch08   db 019h,001h
   db 06ch
   db 04dh
   db 082h
   db 04dh
   db 060h
   db 078h
   db 080h
   db 04dh
   db 060h
   db 081h
   db 04dh
   db 080h
   db 059h
   db 06ch
   db 04dh
   db 082h
   db 04dh
   db 060h
   db 078h
   db 080h
   db 04dh
   db 060h
   db 081h
   db 04dh
   db 080h
   db 059h
   db 06ch
   db 04dh
   db 082h
   db 04dh
   db 060h
   db 078h
   db 080h
   db 04dh
   db 060h
   db 081h
   db 04dh
   db 080h
   db 059h
   db 06ch
   db 04dh
   db 082h
   db 04dh
   db 060h
   db 078h
   db 080h
   db 04dh
   db 060h
   db 081h
   db 04dh
   db 080h
a_p05ch09   db 0bfh
a_instruments db 1
