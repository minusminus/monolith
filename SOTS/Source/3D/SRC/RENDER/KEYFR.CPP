#ifndef KEYFR_CPP
 #define KEYFR_CPP
//=========================================================================



//=========================================================================
//keyframe
//interpoluje sciezki


void setframe(Scene *s,float frame)
{
unsigned long i;
Object *ob;
Camera *cam;

    //interpolacja sciezek dla obiektow
    for(i=0;i<s->obnum;i++)
       {
        ob=s->obtbl[i];
        if((ob->flags&OUNVIS)==0)       //jak widac obiekt w keyframerze
        {
        if(ob->postrnum>0)
          InterpolateT3(ob->postr,frame,&ob->pos,&ob->actpos,ob->postrnum);
        if(ob->scaletrnum>0)
          InterpolateT3(ob->scaletr,frame,&ob->scale,&ob->actscale,ob->scaletrnum);
        if(ob->pivottrnum>0)
          InterpolateT3(ob->pivottr,frame,&ob->pivot,&ob->actpivot,ob->pivottrnum);
        if(ob->rottrnum>0)
          InterpolateTQ(ob->rottr,frame,&ob->rot,&ob->actrot,ob->rottrnum);
        if(ob->morphtrnum>0)
          InterpolateTM(ob->morphtr,frame,ob,s->morphtbl,&ob->actmorph,ob->morphtrnum);
        };
       };

    //interpolacja sciezek dla kamer
//    for(i=0;i<s->camnum;i++)
//       {
//        cam=s->camtbl[i];
        cam=s->cam;
        if(cam->postrnum>0)
          InterpolateT3(cam->postr,frame,&cam->pos,&cam->actpos,cam->postrnum);
        if(cam->trgtrnum>0)
          InterpolateT3(cam->trgtr,frame,&cam->trg,&cam->acttrg,cam->trgtrnum);
        if(cam->rolltrnum>0)
          InterpolateT1(cam->rolltr,frame,&cam->roll,&cam->actroll,cam->rolltrnum);
        if(cam->FOVtrnum>0)
          InterpolateT1(cam->FOVtr,frame,&cam->FOV,&cam->actFOV,cam->FOVtrnum);

//       };

    //interpolacja sciezek dla swiatel
    for(i=0;i<s->lightnum;i++)
       {

       };


};




//=========================================================================
#endif
