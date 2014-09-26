#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "color.h"

int main(){
    int 	screenx,screeny,
            ix,iy,
            i,j,k,l,
            frames,
            er,bailout;
    double	zx,zy,zxn,zyn,
            cx,cy,ccx,ccy,
            sens,
            minx,maxx,miny,maxy,
            xcenter,ycenter,size;
    char	name[256],fname[256];

    FILE *img;
    _color *bitmap,col,*pal;
    int *escapetime;

    screenx=1600/4;
    screeny=1200/4;
    sens=0.085;
    er=2;

    //~ screenx=1600/1;
    //~ screeny=1200/1;

    bailout=64;
    bailout*=2;
    //bailout*=2;
    //bailout*=2;
    //bailout*=2;

    minx=-1.9;
    maxx=minx*-1;
    miny=-1.5;
    maxy=miny*-1;

    ccx=0.49;
    ccy=0.1;

    frames=400;

    //~ escapetime=(double*)malloc(sizeof(double)*screenx*screeny);
    escapetime=(int*)malloc(sizeof(int)*screenx*screeny);
    pal=(_color*)malloc(sizeof(_color)*255);
    populatePal(pal);

    for(l=0;l<frames;l++){
        cx=ccx+(sin(((double)l/frames)*M_PI*4.0)*0.2);
        cy=ccy-(cos(((double)l/frames)*M_PI*6.0)*0.52);

        sprintf(name,"%s_%07d.ppm","julia",l);
        img=fopen(name,"wt");
        fprintf(img,"P3\n%d %d\n255\n",screenx,screeny);
        for(iy=0;iy<screeny;iy++){
            for(ix=0;ix<screenx;ix++){
                zy=miny+iy*(maxy-miny)/screeny;
                zx=minx+ix*(maxx-minx)/screenx;
                for(i=1;i<bailout-1;i++){
                    zxn=zx*zx-zy*zy+cx;
                    zyn=2.0*zx*zy+cy;
                    zx=zxn;
                    zy=zyn;

                    if(zx*zx+zy*zy>er*er){
                        escapetime[iy*screenx+ix]=i+1;
                        break;
                    }
                }
                if(i==bailout-1){
                    escapetime[iy*screenx+ix]=0.0;
                }
            }
            //~ if(iy%(screeny/10)==0){
            //~ fprintf(stderr," -- %.2f%%\n",(iy/(double)screeny)*100.0);
            //~ }
        }

        //~ fprintf(stderr," -- %.2f%%\n",100.0);
        //~ fprintf(stderr," <---- DONE ---->\n");
        //~ fprintf(stderr," Writing to disk!\n");

        fprintf(stderr,"%d ",l);

        for(i=0;i<screeny;i++){
            for(j=0;j<screenx;j++){
                col.r=((1.0-exp(-sens*escapetime[i*screenx+j])));

                //col=getHue(col.r);
                //~ col=getPal(col.r);
                //~ col=getGrad2(col.r);
                if(col.r!=0.0){
                    col=getPalMem(col.r,pal);
                }else{
                    col.r=0;
                    col.g=0;
                    col.b=0;
                }


                //col.r*=255;
                //col.g*=255;
                //col.b*=255;
                fprintf(img,"%d %d %d ",(int)col.r,(int)col.g,(int)col.b);
                escapetime[i*screenx+j]=0;
            }
            fputc('\n',img);
        }

        fclose(img);
    }

    free(escapetime);

    fprintf(stderr," -- Bye\n");

    sprintf(name,"%s","julia");

    sprintf(fname,"./converter %s",name);
    printf("%s\n",fname);
    system(fname);

    sprintf(fname,"rm %s_*.ppm",name);
    printf("%s\n",fname);
    system(fname);

    sprintf(fname,"ffmpeg -s 720x576 -r 25 -i %s_%%07d.png -async 1 -vcodec libx264 %s.mp4",name,name);
    printf("%s\n",fname);
    system(fname);

    return EXIT_SUCCESS;
}
