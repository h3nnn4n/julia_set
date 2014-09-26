#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "color.h"

int main(){
    int 	screenx,screeny,
            ix,iy,
            i,j,k,
            er,bailout;
    double	zx,zy,zxn,zyn,cx,cy,
            sens,
            minx,maxx,miny,maxy,
            xcenter,ycenter,size;

    FILE *img=fopen("julia.ppm","wt");
    _color *bitmap,col,*pal;
    int *escapetime;

    screenx=1600/2;
    screeny=1200/2;
    bailout=256;
    sens=0.17;
    er=2;

    //~ screenx=1600/1;
    //~ screeny=1200/1;
    //~ bailout=256;
    //~ sens=0.02;
    //~ er=2;

    minx=-1.5;
    maxx=minx*-1;
    miny=-1.5;
    maxy=minx*-1;

    cx=0.25;
    cy=0.662;

    //~ escapetime=(double*)malloc(sizeof(double)*screenx*screeny);
    escapetime=(int*)malloc(sizeof(int)*screenx*screeny);
    pal=(_color*)malloc(sizeof(_color)*255);

    fprintf(img,"P3\n%d %d\n255\n",screenx,screeny);

    populatePal(pal);
    if(pal==NULL){
        printf("Shithithishit\n\n");
        return EXIT_FAILURE;
    }

    for(iy=0;iy<screeny;iy++){
        for(ix=0;ix<screenx;ix++){
            zy=miny+iy*(maxy-miny)/screeny;
            zx=minx+ix*(maxx-minx)/screenx;
            for(i=0;i<bailout;i++){
                zxn=zx*zx-zy*zy+cx;
                zyn=2.0*zx*zy+cy;
                zx=zxn;
                zy=zyn;

                if(zx*zx+zy*zy>er*er){
                    escapetime[iy*screenx+ix]=i;
                    break;
                }
            }
            if(i==bailout-1){
                escapetime[iy*screenx+ix]=0.0;
            }
        }
        if(iy%(screeny/10)==0){
            fprintf(stderr," -- %.2f%%\n",(iy/(double)screeny)*100.0);
        }
    }

    fprintf(stderr," -- %.2f%%\n",100.0);
    fprintf(stderr," <---- DONE ---->\n");
    fprintf(stderr," Writing to disk!\n");

    for(i=0;i<screeny;i++){
        for(j=0;j<screenx;j++){
            col.r=((1.0-exp(-sens*escapetime[i*screenx+j])));

            if(col.r<0 || col.r>1.0){
                printf("=> %.18lf\n",col.r);
            }

            //col=getHue(col.r);
            //col=getPal(col.r);
            //col=getGrad2(col.r);
            col=getPalMem(col.r,pal);

            //col.r*=255;
            //col.g*=255;
            //col.b*=255;
            fprintf(img,"%d %d %d ",(int)col.r,(int)col.g,(int)col.b);
        }
        fputc('\n',img);
    }

    fclose(img);
    free(escapetime);

    fprintf(stderr," -- Bye\n");

    return EXIT_SUCCESS;
}
