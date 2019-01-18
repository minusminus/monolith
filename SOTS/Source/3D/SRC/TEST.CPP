#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "vesa32.h"
#include "pread.h"
#include "./texman/texman.h"
#include "memory.h"
#include "./maths/matrix.h"
#include "scene.h"
#include "code.h"


void wait_vbl(void);		// czekanie na synchronizacje pionowa
#pragma aux wait_vbl=\
" mov dx,3dah "\
" w1: "\
" in al,dx "\
" test al,8 "\
" jnz w1"\
" w2: "\
" in al,dx"\
" test al,8"\
" jz w2"\
modify exact [eax edx];

#include "drawtr.h"

#include "./maths/preproc.cpp"

#include "render.cpp"
