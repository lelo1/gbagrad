#include "dat.h"
#include "fns.h"

 bullettype btype[]={
 //  w,h,bild,speed,eingefroren,schaden
	{3*UNIT,4*UNIT,NORMSCHUSS,UNIT,0,1},
	{4*UNIT,2*UNIT,SCHNELLSCHUSS,UNIT*2,180,1},
	{8*UNIT,8*UNIT,BIGBULLET,UNIT,0,1},
	{5*UNIT,5*UNIT,FROSTSCHUSS,UNIT,360,0},
	{3*UNIT,4*UNIT,NEUTSCHUSS,UNIT,0,1},
	{240*UNIT,2*UNIT,STRAHL,0,0,2},
};
bullettype bplayertype[]={
 //  w,h,bild,speed,eingefroren,schaden
	{3*UNIT,4*UNIT,SCHUSS,UNIT/2,0,1},
	{3*UNIT,4*UNIT,LASER,UNIT*3,0,3},
	
};
void 
newbullet(int x, int y, int e, int t, int spy)
{
	bullet *b;
	
	for(b = bulletlist; b < bulletlist + maxbullets; b++)
		if (b->da==0){
			b->da=1;
			b->x=x;
			b->y=y;
			b->e=e;
			b->t=t;
			b->spy=spy;
			if(b->t==5)
				b->spy=10;
			if(b->e)
				b->bt=&btype[b->t];
			else
				b->bt=&bplayertype[b->t];
			return;
		}
}	
void
movebullets(void)
{
	bullet *b;
	
	for(b = bulletlist; b < bulletlist + maxbullets; b++)
		if(b->da){
			if(b->e==0){
				b->x-=b->bt->sp;
				if(b->x<=0)
					b->da=0;
			}else{
				if(b->t==5){
					if(b->spy--==0)
						b->da=0;
					continue;
					}
				b->x+=b->bt->sp;
				b->y+=b->spy;
				if(b->x>=240*UNIT||b->x<=0*UNIT||b->y>160*UNIT||b->y<0*UNIT)
					b->da=0;
			}
		}
}
	