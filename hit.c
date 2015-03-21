#include "dat.h"
#include "fns.h"


int 
hit(int x0,int y0,int w0 ,int h0,int x1,int y1,int w1 ,int h1)
{
	return x0 < x1+w1 && x0 + w0 > x1 && y0 < y1+h1 && y0+h0 > y1;
} 

void
schaden(int s)
{
	leben-=s;
	if(leben<=0)
		gameover();
}
void
treffer(void)
{
	enemy *e;
	bullet*b;
	item *i;
	for(e = enemylist; e < enemylist + maxenemy; e++)
		if(e->da==1&&e->from==NULL){
			if(hit(px,py,pt->w,pt->h,e->x,e->y,e->et->w,e->et->h)){
				e->da=0;
				punkte++;
				if(modus==LEVEL)
					levelup();
				if(e->to!=NULL)
							e->to->from=NULL;
				if(e->t==station)
					schaden(100);
				schaden(1);
				continue;
			}
			for(b = bulletlist; b < bulletlist + maxbullets; b++)
				if (b->da==1&&b->e!=1 &&hit(b->x, b->y, b->bt->w, b->bt->h, e->x, e->y, e->et->w, e->et->h)){
					if(e->t==neutral&&b->e==2)
						continue;
					if(e->schild>0){
						e->schild-=1;
						b->da=0;
						continue;
					}
					else
						if(b->e==2)
							e->ghp-=5;
						else
							e->ghp-=b->bt->schaden+pt->extraschaden;
						b->da=0;
						if(e->ghp<=0){
							e->da=0;
							punkte++;
							if(rand()%100<itemwahr)
								newitem(e->x,e->y);
							if(modus==LEVEL)
								levelup();
							killcount[e->t]++;
							missionerfuellt();
							if(e->to!=NULL)
								e->to->from=NULL;
							if(e->t==7)
								eingefroren=120;
							continue;
						}
				}
			
		}
	for(b = bulletlist; b < bulletlist + maxbullets; b++)
		if (b->da==1&& b->e && hit(b->x, b->y, b->bt->w, b->bt->h, px,py,pt->w,pt->h)){      
			b->da=0;
			schaden(b->bt->schaden);
			eingefroren+=b->bt->eingefroren;
			continue;
		}	
	for(i=itemlist;i<itemlist+maxitem;i++)
		if(i->da==1&&hit(i->x,i->y,itw,ith,px,py,pt->w,pt->h)){
			i->da=0;
			itemwirkung();
			continue;
		}
}
