;opis face'ow dla obiektu
;te face'y musza byc powtorzone 6 razy -> wtedy bedzie caly obiekt
;powtorzenia z dodaniem ilosci wierzcholkow na kazda czzesc w stosunku do
;poprzedniej

;w sumie jest tu 20 face'ow
mainface:
;kostka gorna [bez dolnej sciany]
db 5,6,2
db 5,2,1
db 5,4,7
db 5,7,6
db 6,7,3
db 6,3,2
db 2,3,0
db 2,0,1
db 1,0,4
db 1,4,5
db 4,0,3
db 4,3,7
;slupek do srodka [tylko boczne sciany, dol i gora nie potrzebne]
db 13,14,10
db 13,10,9
db 14,15,11
db 14,11,10
db 9,8,12
db 9,12,13
db 12,8,11
db 12,11,15


;opis pktow wzorcowego szescianu
cubepoints:
;1 czesc
db -25,125,-25     ; cube
db -25,125,25
db 25,125,25
db 25,125,-25
db -25,75,-25
db -25,75,25
db 25,75,25
db 25,75,-25
db -10,75,-10      ; slupek
db -10,75,10
db 10,75,10
db 10,75,-10
db -10,10,-10
db -10,10,10
db 10,10,10
db 10,10,-10
;2 czesc
db -25,-125,25     ; cube
db -25,-125,-25
db 25,-125,-25
db 25,-125,25
db -25,-75,25
db -25,-75,-25
db 25,-75,-25
db 25,-75,25
db -10,-75,10      ; slupek
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
db -75,-10,-10      ; slupek
db -75,-10,10
db -75,10,10
db -75,10,-10
db 0,-10,-10
db 0,-10,10
db 0,10,10
db 0,10,-10
;4 czesc
db 125,25,-25     ; cube
db 125,25,25
db 125,-25,25
db 125,-25,-25
db 75,25,-25
db 75,25,25
db 75,-25,25
db 75,-25,-25
db 75,10,-10      ; slupek
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
db -10,-10,-75      ; slupek
db -10,10,-75
db 10,10,-75
db 10,-10,-75
db -10,-10,-10
db -10,10,-10
db 10,10,-10
db 10,-10,-10
;6 czesc
db -25,25,125     ; cube
db -25,-25,125
db 25,-25,125
db 25,25,125
db -25,25,75
db -25,-25,75
db 25,-25,75
db 25,25,75
db -10,10,75      ; slupek
db -10,-10,75
db 10,-10,75
db 10,10,75
db -10,10,10
db -10,-10,10
db 10,-10,10
db 10,10,10
