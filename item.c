#include "dat.h"
#include "fns.h" 
void
newitem(int x,int y)
{
	item *i;
	for(i=itemlist;i<itemlist+maxitem;i++)
		if(i->da==0){
			i->da=1;
			i->x=x;
			i->y=y;
			return;
		}
}
void
moveitem(void)
{
	item *i;
	
	for(i=itemlist;i<itemlist+maxitem;i++)
		if(i->da){
			i->x+=itemspeed;
			if(i->x>=240*UNIT)
				i->da=0;
		}
}
void
itemwirkung(void)
{
	int iw;
	iw=rand()%14;
	enemy *e;
	switch(iw){
	case 1:
	case 2:
		leben++;
		break;
	case 3:
	case 4:
		eingefroren= 120;
		break;
	case 5:
	case 6:
	case 7:
		ammo[1]+=100;
		break;
	case 8:
	case 9:
	case 10:
		if(ammo[1]>100)
		ammo[1]-=100;
		break;
	case 11:
		itemspeed-=itemspeed/4;
		break;
	case 12:
		itemspeed+=itemspeed/4;
		break;
	case 13:
	case 14:
		
		for(e = enemylist; e < enemylist + maxenemy; e++)
			e->schild=20;
		break;
	}
}



























