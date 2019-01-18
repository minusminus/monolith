//3d engine for deus city
#ifndef _included_3d_h_
#define _included_3d_h_



#include ".\3d\deus\matrix.h"
#include ".\3d\deus\texman.h"
#include ".\3d\deus\scene.h"

#include ".\3d\deus\bsort.h"
#include ".\3d\deus\drawtr.h"


void preprocesskeys(Scene *sc);
void render(Scene *sc,unsigned long *buf,unsigned long *zbuf,float frm);




#endif