#include "dat.h"
#include "fns.h"

enemytype etype[]={
//  x,y,bild,speed,ghp,bt,size
	{6*UNIT,8*UNIT,NORMALEREN,UNIT/2,3,0,0},
	{8*UNIT,6*UNIT,JAEGERSCHWER,2*UNIT,10,-1,0},
	{6*UNIT,6*UNIT,JAEGERLEICHT,3*UNIT,1,-1,0},
	{6*UNIT,8*UNIT,LASEREN,UNIT/2,10,1},
	{8*UNIT,7*UNIT,BIGBULLETEN,UNIT/3,20,2,0},
	{4*UNIT,8*UNIT,TODEN,UNIT/5,5,-1},
	{3*UNIT,8*UNIT,MAUER,UNIT/3,1000,-1,0},
	{4*UNIT,8*UNIT,FROSTER,UNIT/2,5,3,0},
	{5*UNIT,8*UNIT,BEAM,UNIT/2,1,1,0},
	{8*UNIT,6*UNIT,SCHUETZER,UNIT/6,30,-1,0},
	{16*UNIT,14*UNIT,STATION,0,200,1,1},
	{16*UNIT,8*UNIT,NEUTRAL,UNIT/5,40,4,4},
	{8*UNIT,8*UNIT,STRAHLEN,0,10,0,0},
};
	
enemy *
choose(enemy *f)
{
	enemy *e;
	int n;
	n=0;
	for(e = enemylist; e < enemylist + maxenemy; e++)
		if(e->da==1 && e->from == NULL && e != f)
			n++;
	if(n==0)
		return NULL;
	n=rand()%n;
	for(e = enemylist; e < enemylist + maxenemy; e++)
		if(e->da==1 && e->from == NULL && e != f&&n--==0)
			return e;
	return NULL;
}
void
newenemy(int x,int y,int t)
{
	enemy *e;
	if(t==neutral&&count(t)>=5)
		return;
	for(e = enemylist; e < enemylist + maxenemy; e++)
		if(e->da==0){
			e->to = NULL;
			e->from = NULL;
			if(t==9){
				e->to=choose(e);
				if(e->to!=NULL)
					e->to->from=e;
			}
			e->da=1;
			e->x=x;
			e->y=y;
			e->t=t;
			e->et=&etype[e->t];
			e->ghp=e->et->ghp;
			e->schild=0;
			return;
		}
}
void
moveenemy(void)
{
	enemy *e;
	
	for(e = enemylist; e < enemylist + maxenemy; e++)
		if(e->da && emp==0){
			e->x+=e->et->sp;
			if (e->t==8&& e->y>=py-5 && e->y<=py+5 )
				e->y=rand()%(152*UNIT);
			if (e->t==station){
				if(e->d==0){
					e->y+=UNIT/2;
					if(e->y>152*UNIT)
						e->d=1;
				}
				else{
					e->y-=UNIT/2;
					if(e->y<1*UNIT)
						e->d=0;
				}
			}
			if(e->x>=240*UNIT){
				e->da=0;
				if(e->from != NULL){
					e->from->to = choose(e->from);
					if(e->from->to != NULL)
						e->from->to->from = e->from;
				}
				if(e->to != NULL)
					e->to->from = NULL;
				if(e->t==5)
					schaden(1);
			}
		}
}