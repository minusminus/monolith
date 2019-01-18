//********************************************************************
//usuwa texture
Tex::~Tex(void)
{
delete this->texaddr;
};


//********************************************************************
//tworzy bufor textur
Texman::Texman(int num)
{
this->number=num;
this->textures=new Tex[num];
this->free=0;
};


//********************************************************************
//usuwa bufor textur
Texman::~Texman(void)
{
int i;

for(i=0;i<this->number;i++)	 //usun wpisy w buforze textur
   delete this->textures[i].texaddr;
delete this->textures;		 //usun tablice textur
};






//********************************************************************
//dodaje do bufora texture o danej nazwie
int Texman::addtex(const char *file)
{
Tex *t;
int i=0;
int is=0;
char *fname;


while((is==0)&&(i<this->free))
{			      //sprawdz czy nie ma juz takiej textury
if(strcmp(file,(const char *)(this->textures[i].texname))==0)
  {
  is=1;
  } else {i++;};
};

if(is==0)
{
//dolozenie textury
t=&this->textures[this->free];	  //gdzie
this->free++;
strcpy((char *)(&t->texname),file);	   //kopiuj nazwe
t->texcount=1;
//ladowanie textury z pliku
t->texaddr=(unsigned long *)read_png((char *)(file),&t->width,&t->height);
return this->free-1;
} else
{      //juz taka jest
return i;
};

};





//********************************************************************
//usuwa texture z bufora
void Texman::remtex(int num)
{
Tex *t;

t=&this->textures[num];    //gdzie
t->texcount--;
if(t->texcount==0)
  {		  //to usun texture
  delete t->texaddr;
  };
};





//********************************************************************
//podaje adres textury o danym numerze
void *Texman::gettexaddy(int num)
{
return this->textures[num].texaddr;
};
