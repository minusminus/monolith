#ifndef SCENE_H
#define SCENE_H
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
     float frame;	//numer klatki
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
     float frame;	//numer klatki
     float ease_from;
     float ease_to;
     float vala;	//wartosci dla danej klatki
     float valb;
     float valc;
     float der1a;	//pochodne wchodzace i wychodzace z klucza
     float der2a;	//dla kazdej z 3 wartosci
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
     quat q;		//quaterion
     float angle;	//roznica katow miedzy nastepna a aktualna klatka
     int extraspin;
     quat qa;		//pochodna wchodzaca
     quat qb;		//i wychodzaca quaterionu


     friend void readtrackQ(TrackQ *t,FILE *f);

};

class TrackM
{
public:
     float frame;	//numer klatki
     unsigned long number;	//numer wpisu w buforze morfingu

     friend void readtrackM(TrackM *t,FILE *f);

};


//======================================================================
//bufor morphingu
//kazdy wpis ma tyle pktow co morphowany obiekt

class Morphex	//element bufora morphingu
{
public:
Vector coords;	//wspolrzedne oryginalne w danej klatce
Vector norms;	//normalsy oryginalne
Vector dv;     //przyrosty wspolrzednych na klatke
Vector dn;    //przyrosty normalsow na kaltke

};


class Morpher
{
public:
unsigned long mnum;	//ilosc wpisow
Morphex *mtbl;	//kolejne wpisy dla kolejnych wierzcholkow

Vector box[8];	//boundbox
Vector dbox[8]; //i jego delty

//friend void readmorpher(Morpher *m,FILE *f);

Morpher(FILE *f);
~Morpher(void);

};



//======================================================================
//bufor tekstur





//======================================================================
//vertex

class Vertex
{
public:
   Vector vorig;      //wspolrzedne pktu
   Vector v3d;
   Vector norig;      //normalsy znormalizowane
   Vector n3d;
   float x2d;		//wspolrzedne 2d
   float y2d;
   TexVec tex;	      //wspolrzedne textury
   unsigned long flags;    //dodatkowe pole opisu widocznosci,perspektywy itp


friend void readvertex(Vertex *v,FILE *f);

};

//flagi dla punktu
#define VPERSP 0x1	//flaga perspektywy
#define VIS1 0X2	//flagi obcinania wzgledem scian
#define VIS2 0X4
#define VIS3 0X8
#define VIS4 0X10
#define VIS5 0X20
#define VIS6 0X40




//======================================================================
//face

class Object;

class Face
{
public:
   Vertex *p1;		//adresy 3 pktow
   Vertex *p2;
   Vertex *p3;
   Vector normals;     //wektor normalny do face'a
   int zsum;
   unsigned long *texaddr;	//adres textury
   unsigned long flags;    //flagi [jak w vertexie]
//   void (*clipper)(Face *tr);    //procedura obcinajaca
//   void (*render)(Face *tr);	   //procedura rysujaca
   int d12,d23,d13;	      //delty dla trojakta
   int dz12,dz23,dz13;	      //delty dla zbufora
   int dzx;		      //stala delta w poziomie

friend void readface(Object *o,Face *fc,FILE *f);

};


//flagi dla face'a
#define FP12 0x80000000 //czesc 1->2	bit 31
#define FP23 0x40000000 //czesc 2->3	bit 30
#define FPUNVIS 0x3fffffff	//maska flag widocznosci



//======================================================================
//obiekty

class Object
{
public:
   unsigned long facenum;	//ilosc face'ow
   unsigned long vertnum;	//ilosc vertexow
   Face *facetbl;      //adres tablicy face'ow obiektu
   Vertex *vertbl;     //tablica vertexow obiektu
   Matrix obmat;     //macierz obiektu [we wasnym ukladzie
   Matrix eyemat;    //macierz po kamerze i hierarchii
   Matrix backeyemat; //macierz translacji kamery do ukladu obiektu
   Vector transl;    //przesuniecie w eyematrix
   Vector pos;	      //pozycja [wektor przesuniecia]
   Vector pivot;      //pivot point
   Vector scale;      //wektor skalowania
   quat rot;	      //kwaterion obrotu
   Object *fatherob;	 //obiekt 'rodzic'
   unsigned long flags;

   Vector box[8];      //boundbox

   unsigned long postrnum;	//ilosc wpisow sciezki pozycji
   unsigned long actpos;
   Track3 *postr;		//wskaznik do sciezki pozycji
   unsigned long scaletrnum;	  //ilosc wpisow sciezki skalowania
   unsigned long actscale;
   Track3 *scaletr;		  //wskaznik do sciezki skalowania
   unsigned long pivottrnum;	  //ilosc wpisow sciezki pivot'a
   unsigned long actpivot;
   Track3 *pivottr;		  //wskaznik do sciezki pivot'a
   unsigned long rottrnum;	//ilosc wpisow sciezki obrotow
   unsigned long actrot;
   TrackQ *rottr;		//wskaznik do sciezki obrotow
   unsigned long morphtrnum;	  //ilosc wpisow sciezki morfingu
   unsigned long actmorph;
   TrackM *morphtr;		  //wskaznik do sciezki morfingu


   Object(FILE *f);
   ~Object(void);


   friend void makeobmat(Object *o);

};

//flagi dla obiektow
#define OUNVIS 0x80000000	//niewidoczny w keyframerze
#define OUNVISBOX 0X40000000	//niewidoczny z boxbound'a



//======================================================================
//kamery

class Camera
{
public:
  unsigned long flags;	//flagi
  Matrix mat;	     //macierz obrotu
  Vector pos;		//pozycja kamery
  Vector trg;	     //punkt na ktory kamera patrzy
  Vector campos;     //pozycja kamery dla transformacji obiektow
  float FOV;		//pole widzenia
  float roll;
  float focus;		//dlugosc wektora kamery
  float cvalx;		 //wartosc dla clippingu 3d
  float cvaly;
  float aspectratio;
  float scaleX;
  float scaleY;
  float zmin;		//plaszczyzna obciniania
  Object *fatherob;		//dla pozycji
  Object *fatherob2;		//dla trg
   unsigned long postrnum;	//ilosc wpisow sciezki pozycji
   unsigned long actpos;	//ostatnio czytany klucz
   Track3 *postr;		//wskaznik do sciezki pozycji
   unsigned long trgtrnum;	//ilosc wpisow sciezki trg
   unsigned long acttrg;
   Track3 *trgtr;		//wskaznik do sciezki trg
   unsigned long rolltrnum;	 //ilosc wpisow sciezki obrotow
   unsigned long actroll;
   Track1 *rolltr;		 //wskaznik do sciezki obrotow
   unsigned long FOVtrnum;	//ilosc wpisow sciezki FOV
   unsigned long actFOV;
   Track1 *FOVtr;		//wskaznik do sciezki FOV


  Camera(FILE *f);
  ~Camera(void);



  friend void makecammat(Camera *cam,long ScreenX,long ScreenY);

};






//======================================================================
//swiatla

class SpotLight
{
public:
  unsigned long flags;	//flagi
  float r,g,b;		//kolor ambientu
  Vector pos;
  Vector trg;
};


class OmniLight
{
public:
  unsigned long flags;	//flagi
  float r,g,b;		//kolor swiatla
  Vector pos;		//pozycja swiatla
};


class AmbientLight
{
public:
//  Vector ambient;	  //kolor ambientu
  float r,g,b;		  //kolor
  unsigned long trnum;
  unsigned long acttr;
  Track3 *tr;	       //i sciezka koloru ambientu
};


//======================================================================
//def wskaznikow do obiektow
typedef Object *optr;
typedef Face *fptr;
typedef Camera *cptr;
typedef OmniLight *lptr;
typedef Morpher *mptr;
typedef unsigned long *tptr;

//======================================================================
//cala scena

class Scene
{
public:
  unsigned long obnum;	//ilosc obiektow
  unsigned long camnum; 	//ilosc kamer
  unsigned long lightnum;	//ilosc swiatel
  int activecam;	 //numer akytwnej kamery
  float firstfr;		   //pierwsza
  float lastfr; 		   //i ostatnia klatka
  float zmin;

  float scrX;		//wielkosc ekranu [musi byc mniejsza niz wielkosc
  float scrY;		//bufora
  float bufx;		//wielkosc bufora
  float bufy;
  float perspx; 	//przesuniecie ekranu w buforze
  float perspy;

//  Object **obtbl;	  //tablica adresow obiektow
//  Camera **camtbl;	  //tablica adresow kamer
//  OmniLight **lighttbl;     //tablica adresow swiatel
  optr *obtbl;
  cptr *camtbl;
  lptr *lighttbl;

  unsigned long framenum;	//ilosc klatek
  float frame;		     //numer aktualnej klatki

  unsigned long facestodraw;	//ilosc face'ow do narysowania w drawtbl
//  Face **drawtbl;	  //tablica face'ow do narysowania,sortowania,itd
//  Face **drawtbl2;	  //pomocnicza tablica rysowania face'ow
  fptr *drawtbl;
  fptr *drawtbl2;
  Camera *cam;		//adres aktualnej kamery do renderingu

//  Vector ambient;	  //kolor ambientu
//  unsigned long ambtrnum;
//  Track3 *ambtr;	    //i sciezka koloru ambientu
  AmbientLight ambient;

  unsigned long morphnum;	//ilosc wpisow w buforze morphingu
  mptr *morphtbl;	    //tablica adresow kolejnych wpisow w buforze

  unsigned long texnum; 	//ilosc textur
  tptr *textbl; 		//tablica adresow textur

  Scene(const char *file,Texman *texman);
  ~Scene(void);

  void setresolution(float scx,float scy,	//ustawienia renderingu
		     float bfx,float bfy,
		     float px, float py);

  //ustawia wartosci dla danej klatki
  friend void setframe(Scene *s,float frame);
  //ustawia adres odpowiedniej kamery
  friend void setcamera(Scene *sc);
  //renderuje scene
  friend void render(Scene *sc);

};





//=========================================================================
#endif
