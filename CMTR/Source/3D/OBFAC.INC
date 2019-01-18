;opis face'ow dla obiektu
;te face'y musza byc powtorzone 6 razy -> wtedy bedzie caly obiekt
;powtorzenia z dodaniem ilosci wierzcholkow na kazda czzesc w stosunku do
;poprzedniej

;w sumie jest tu 20 face'ow
mainface:
;kostka gorna [bez dolnej sciany]
db 6,7,3
db 6,3,2
db 6,5,8
db 6,8,7
db 7,8,4
db 7,4,3
db 3,4,1
db 3,1,2
db 2,1,5
db 2,5,6
db 5,1,4
db 5,4,8
;slupek do srodka [tylko boczne sciany, dol i gora nie potrzebne]
db 14,15,11
db 14,11,10
db 15,16,12
db 15,12,11
db 10,9,13
db 10,13,14
db 13,9,12
db 13,12,16


;opis pktow wzorcowego szescianu
cubepoints:
;1 czesc
db -25,125,-25	   ; cube
db -25,125,25
db 25,125,25
db 25,125,-25
db -25,75,-25
db -25,75,25
db 25,75,25
db 25,75,-25
db -10,75,-10	   ; slupek
db -10,75,10
db 10,75,10
db 10,75,-10
db -10,10,-10
db -10,10,10
db 10,10,10
db 10,10,-10
;2 czesc
db -25,-125,25	   ; cube
db -25,-125,-25
db 25,-125,-25
db 25,-125,25
db -25,-75,25
db -25,-75,-25
db 25,-75,-25
db 25,-75,25
db -10,-75,10	   ; slupek
db -10,-75,-10
db 10,-75,-10
db 10,-75,10
db -10,-10,10
db -10,-10,-10
db 10,-10,-10
db 10,-10,10
;3 czesc
db -125,-25,-25     ; cube
db -125,-25,25
db -125,25,25
db -125,25,-25
db -75,-25,-25
db -75,-25,25
db -75,25,25
db -75,25,-25
db -75,-10,-10	    ; slupek
db -75,-10,10
db -75,10,10
db -75,10,-10
db 0,-10,-10
db 0,-10,10
db 0,10,10
db 0,10,-10
;4 czesc
db 125,25,-25	  ; cube
db 125,25,25
db 125,-25,25
db 125,-25,-25
db 75,25,-25
db 75,25,25
db 75,-25,25
db 75,-25,-25
db 75,10,-10	  ; slupek
db 75,10,10
db 75,-10,10
db 75,-10,-10
db 0,10,-10
db 0,10,10
db 0,-10,10
db 0,-10,-10
;5 czesc
db -25,-25,-125     ; cube
db -25,25,-125
db 25,25,-125
db 25,-25,-125
db -25,-25,-75
db -25,25,-75
db 25,25,-75
db 25,-25,-75
db -10,-10,-75	    ; slupek
db -10,10,-75
db 10,10,-75
db 10,-10,-75
db -10,-10,-10
db -10,10,-10
db 10,10,-10
db 10,-10,-10
;6 czesc
db -25,25,125	  ; cube
db -25,-25,125
db 25,-25,125
db 25,25,125
db -25,25,75
db -25,-25,75
db 25,-25,75
db 25,25,75
db -10,10,75	  ; slupek
db -10,-10,75
db 10,-10,75
db 10,10,75
db -10,10,10
db -10,-10,10
db 10,-10,10
db 10,10,10
