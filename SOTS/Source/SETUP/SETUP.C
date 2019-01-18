#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <midasdll.h>
#include "vga.h"



void main(void)
{

MIDASstartup();

MIDASconfig();


MIDASsaveConfig("deus.cfg");




MIDASclose();

};

