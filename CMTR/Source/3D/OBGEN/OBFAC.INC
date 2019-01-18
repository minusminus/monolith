;opis face'ow dla obiektu
;te face'y musza byc powtorzone 6 razy -> wtedy bedzie caly obiekt
;powtorzenia z dodaniem ilosci wierzcholkow na kazda czzesc w stosunku do
;poprzedniej

;w sumie jest tu 20 face'ow
mainface:
;kostka gorna [bez dolnej sciany]
db 1,2,3
db 1,3,4
db 8,4,3
db 8,3,7
db 1,4,6
db 1,8,5
db 1,2,5
db 5,2,6
db 2,3,7
db 7,6,2
db 5,6,7
db 7,6,2
;slupek do srodka [tylko boczne sciany, dol i gora nie potrzebne]
db 13,9,10
db 13,10,14
db 10,11,15
db 15,14,10
db 16,12,11
db 16,11,15
db 16,13,9
db 9,12,13


;opis pktow wzorcowego szescianu
cubepoints:
;1 czesc
db -25,25,75		;kostka
db -25,25,125
db 25,25,125
db 25,25,75
db -25,-25,75
db -25,-25,125
db 25,-25,125
db 25,-25,75
db -10,10,75		;nozka
db -10,-10,75
db 10,-10,75
db 10,10,75
db -10,10,10
db -10,-10,10
db 10,-10,10
db 10,10,10
;2 czesc
db 75,25,-25
db 75,25,25
db 125,25,25
db 125,25,-25
db 75,-25,-25
db 75,-25,25
db 125,-25,25
db 125,-25,-25
db 75,10,-10		;nozka
db 75,10,10
db 75,-10,10
db 75,-10,-10
db 10,10,-10
db 10,10,10
db 10,-10,10
db 10,-10,-10
;3 czesc
db -25,25,-75		 ;kostka
db -25,25,-125
db 25,25,-125
db 25,25,-75
db -25,-25,-75
db -25,-25,-125
db 25,-25,-125
db 25,-25,-75
db -10,10,-75		 ;nozka
db -10,-10,-75
db 10,-10,-75
db 10,10,-75
db -10,10,-10
db -10,-10,-10
db 10,-10,-10
db 10,10,-10
;4 czesc
db -75,25,-25
db -75,25,25
db -125,25,25
db -125,25,-25
db -75,-25,-25
db -75,-25,25
db -125,-25,25
db -125,-25,-25
db -75,10,-10		 ;nozka
db -75,10,10
db -75,-10,10
db -75,-10,-10
db -10,10,-10
db -10,10,10
db -10,-10,10
db -10,-10,-10
;5 czesc
db -25,-125,-25
db -25,-125,25
db 25,-125,25
db 25,-125,-25
db -25,-75,-25
db -25,-75,25
db 25,-75,25
db 25,-75,-25
db -10,-75,-10		 ;nozka
db -10,-75,10
db 10,-75,10
db 10,-75,-10
db -10,-10,-10
db -10,-10,10
db 10,-10,10
db 10,-10,-10
;6 czesc
db -25,125,-25
db -25,125,25
db 25,125,25
db 25,125,-25
db -25,75,-25
db -25,75,25
db 25,75,25
db 25,75,-25
db -10,75,-10		;nozka
db -10,75,10
db 10,75,10
db 10,75,-10
db -10,10,-10
db -10,10,10
db 10,10,10
db 10,10,-10
