;***********************************************************************
;opis struktur (obiektow) dla asmowych procedur
;***********************************************************************


face_s struc
       f_v1 dd ?	   ;\
       f_v2 dd ?	   ; 3 adresy pktow
       f_v3 dd ?	   ;/
       f_nx dd ?	   ;\
       f_ny dd ?	   ; normalny do face'a
       f_nz dd ?	   ;/
       f_zsum dd ?	   ;suma zetow
       f_texaddy dd ?	   ;adres textury
       f_flags dd ?	   ;flagi
       f_d12 dd ?
       f_d23 dd ?
       f_d13 dd ?
       f_dz12 dd ?
       f_dz23 dd ?
       f_dz13 dd ?
       f_dzx dd ?
ends

vert_s struc
       v_vox dd ?
       v_voy dd ?
       v_voz dd ?
       v_vx dd ?
       v_vy dd ?
       v_vz dd ?
       v_nox dd ?
       v_noy dd ?
       v_noz dd ?
       v_nx dd ?
       v_ny dd ?
       v_nz dd ?
       v_x2d dd ?
       v_y2d dd ?
       v_tx dd ?
       v_ty dd ?
       v_flags dd ?
ends