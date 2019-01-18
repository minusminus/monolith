//*************************************************************************
//NIEAKTUALNE
//*************************************************************************

#ifndef LOADER_H
#define LOADER_H

//=========================================================================





//======================================================================
//quaterion
typedef struct
{
        float w,x,y,z;
} quat;


//======================================================================
//sciezki interpolacji


class Track1
{
public:
     float frame;       //numer klatki
     float ease_from;
     float ease_to;
     float val;        //wartosci dla danej klatki
     float der1;       //pochodne wchodzace i wychodzace z klucza
     float der2;

     friend void readtrack1(Track1 *t,FILE *f);

};


class Track3
{
public:
     float frame;       //numer klatki
     float ease_from;
     float ease_to;
     float vala;        //wartosci dla danej klatki
     float valb;
     float valc;
     float der1a;       //pochodne wchodzace i wychodzace z klucza
     float der2a;       //dla kazdej z 3 wartosci
     float der1b;
     float der2b;
     float der1c;
     float der2c;

     friend void readtrack3(Track3 *t,FILE *f);

};

class TrackQ
{
public:
     float frame;
     float ease_from;
     float ease_to;
     quat q;            //quaterion
     float angle;       //roznica katow miedzy nastepna a aktualna klatka
     quat qa;           //pochodna wchodzaca
     quat qb;           //i wychodzaca quaterionu


     friend void readtrackQ(TrackQ *t,FILE *f);

};

class TrackM
{
public:
     float frame;       //numer klatki
     unsigned long number;      //numer wpisu w buforze morfingu

     friend void readtrackM(TrackM *t,FILE *f);

};





//======================================================================
//bufor morphingu
//kazdy wpis ma tyle pktow co morphowany obiekt

class Morpher   //element bufora morphingu
{
public:
Vector dv;     //przyrosty wspolrzednych na klatke
Vector dn;    //przyrosty normalsow na kaltke


friend void readmorpher(Morpher *m,FILE *f);

};






//======================================================================
//vertex

class Vertex
{
public:
   Vector vorig;      //wspolrzedne pktu
   Vector v3d;
   Vector norig;      //normalsy znormalizowane
   Vector n3d;
   float x2d;           //wspolrzedne 2d
   float y2d;
   TexVec tex;        //wspolrzedne textury
   unsigned long flags;    //dodatkowe pole opisu widocznosci,perspektywy itp


friend void readvertex(Vertex *v,FILE *f);

};






//======================================================================
//face

class Object;

class Face
{
public:
   Vertex *p1;          //adresy 3 pktow
   Vertex *p2;
   Vertex *p3;
   Vector normals;     //wektor normalny do face'a
   float zsum;
   unsigned long *texaddr;      //adres textury
   unsigned long flags;    //flagi [jak w vertexie]
   void (*clipper)(Face *tr);    //procedura obcinajaca
   void (*render)(Face *tr);     //procedura rysujaca

friend void readface(Object *o,Face *fc,FILE *f);

};






//======================================================================
//obiekty

class Object
{
public:
   unsigned long facenum;       //ilosc face'ow
   unsigned long vertnum;       //ilosc vertexow
   Face *facetbl;      //adres tablicy face'ow obiektu
   Vertex *vertbl;     //tablica vertexow obiektu
   Matrix obmat;     //macierz obiektu [we wasnym ukladzie
   Matrix eyemat;    //macierz po kamerze i hierarchii
   Vector pos;        //pozycja [wektor przesuniecia]
   Vector pivot;      //pivot point
//   unsigned long succnum;         //ilosc potomkow
//   Object **sonob;       //obiekt 'potomny'
   Object *fatherob;     //obiekt 'rodzic'
   unsigned long flags;

   unsigned long postrnum;      //ilosc wpisow sciezki pozycji
   unsigned long actpos;
   Track3 *postr;               //wskaznik do sciezki pozycji
   unsigned long scaletrnum;      //ilosc wpisow sciezki skalowania
   unsigned long actscale;
   Track3 *scaletr;               //wskaznik do sciezki skalowania
   unsigned long pivottrnum;      //ilosc wpisow sciezki pivot'a
   unsigned long actpivot;
   Track3 *pivottr;               //wskaznik do sciezki pivot'a
   unsigned long rottrnum;      //ilosc wpisow sciezki obrotow
   unsigned long actrot;
   TrackQ *rottr;               //wskaznik do sciezki obrotow
   unsigned long morphtrnum;      //ilosc wpisow sciezki morfingu
   unsigned long actmorph;
   TrackM *morphtr;               //wskaznik do sciezki morfingu


   Object(FILE *f);
   ~Object(void);
};






//======================================================================
//kamery

class Camera
{
public:
  unsigned long flags;  //flagi
  Matrix rotmat;        //macierz obrotu
  Vector pos;           //pozycja kamery
  Vector trg;        //punkt na ktory kamera patrzy
  float FOV;            //pole widzenia
  float roll;
  Object *fatherob;             //dla pozycji
  Object *fatherob2;            //dla trg
   unsigned long postrnum;      //ilosc wpisow sciezki pozycji
   unsigned long actpos;        //ostatnio czytany klucz
   Track3 *postr;               //wskaznik do sciezki pozycji
   unsigned long trgtrnum;      //ilosc wpisow sciezki trg
   unsigned long acttrg;
   Track3 *trgtr;               //wskaznik do sciezki trg
   unsigned long rolltrnum;      //ilosc wpisow sciezki obrotow
   unsigned long actroll;
   Track1 *rolltr;               //wskaznik do sciezki obrotow
   unsigned long FOVtrnum;      //ilosc wpisow sciezki FOV
   unsigned long actFOV;
   Track1 *FOVtr;               //wskaznik do sciezki FOV


  Camera(FILE *f);
  ~Camera(void);

};






//======================================================================
//swiatla

class SpotLight
{
public:
  unsigned long flags;  //flagi
  float r,g,b;          //kolor ambientu
  Vector pos;
  Vector trg;
};


class OmniLight
{
public:
  unsigned long flags;  //flagi
  float r,g,b;          //kolor swiatla
  Vector pos;           //pozycja swiatla
};


class AmbientLight
{
public:
//  Vector ambient;       //kolor ambientu
  float r,g,b;            //kolor
  unsigned long trnum;
  unsigned long acttr;
  Track3 *tr;          //i sciezka koloru ambientu
};



//======================================================================
//cala scena

class Scene
{
public:
  unsigned long obnum;  //ilosc obiektow
  unsigned long camnum;         //ilosc kamer
  unsigned long lightnum;       //ilosc swiatel
  unsigned long activecam;         //numer akytwnej kamery
  float firstfr;                   //pierwsza
  float lastfr;                    //i ostatnia klatka

  Object **obtbl;       //tablica adresow obiektow
  Camera **camtbl;      //tablica adresow kamer
  Light **lighttbl;     //tablica adresow swiatel

  unsigned long framenum;       //ilosc klatek
  float frame;               //numer aktualnej klatki

  unsigned long facestodraw;    //ilosc face'ow do narysowania w drawtbl
  Face **drawtbl;       //tablica face'ow do narysowania,sortowania,itd
  Face **drawtbl2;      //pomocnicza tablica rysowania face'ow

  AmbientLight ambient;

  unsigned long morphnum;       //ilosc wpisow w buforze morphingu
  Morpher **morphtbl;           //tablica adresow kolejnych wpisow w buforze


  Scene(const char *file);
  ~Scene(void);

};




//including code for loader
#include "loader.cpp"


//=========================================================================
#endif
