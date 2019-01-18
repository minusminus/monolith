/*
TEXTURES MANAGER
tylko 32 bitowe /narazie/
*/

#ifndef texman_h
#define texman_h

class Tex
{
public:
unsigned char texname[12];	//nazwa pliku z textura
int texcount;			//ilosc odwolan do textury
long width,height;		 //szerokosc,wysokosc
void *texaddr;			//adres textury w pamieci

~Tex(void);

};


class Texman		//manager textur
{
public:
Tex *textures;		//tablica textur
int number;		//ilosc textur
int free;		//aktualna ilosc wczytanych textur

Texman(int num);
~Texman(void);

int addtex(const char *file);	    //dodanie textury - zwraca numer pozycji
void remtex(int num);		    //usuwa texture o danym numerze
void *gettexaddy(int num);	    //zwraca adres textury o podanym numerze

};




#include "texman.cpp"

#endif