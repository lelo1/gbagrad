#include "dat.h"
#include "fns.h"  

int levelpunkte[]=
{0,30,60,80,110,150,
190,230,270,310,350};

int
exists(int t)
{
	enemy *e;
	for(e = enemylist; e < enemylist + maxenemy; e++)
		if(e->da==1&& e->t==t)
			return 1;
	return 0;
			
}
int
count(int t)
{
	enemy *e;
	int n;
	n=0;
	for(e = enemylist; e < enemylist + maxenemy; e++)
		if(e->da==1&& e->t==t)
			n++;
	return n;
			
}
void
spawn(void)
{
	int t;
	enemy *e;
	switch(modus){
	case ARCADE:
		if(rand()%100<2){
			do t=rand()%entypen;
			while(t==station);
			newenemy(0,rand()%(152*UNIT), t);
		}
		break;
	case LEVEL:
		switch(level){
		case 1:
			if(rand()%100<1)
				newenemy(30,rand()%(152*UNIT),normaleren);
			break;
		case 2:
			if(rand()%100<3)
				newenemy(0,rand()%(152*UNIT),normaleren);
			break;
		case 3:
			if(rand()%100<1)
				newenemy(0,rand()%(152*UNIT),jaegerleicht);
			break;
		case 4:
			if(rand()%100<3)
				newenemy(0,rand()%(152*UNIT),jaegerleicht);
			break;
		case 5:
			if(rand()%100<1)
				newenemy(0,rand()%(152*UNIT),normaleren);
			if(rand()%100<1)
				newenemy(0,rand()%(152*UNIT),jaegerleicht);
			break;
		case 6:
			if(rand()%100<3)
				newenemy(0,rand()%(152*UNIT),normaleren);
			if(rand()%100<3)
				newenemy(0,rand()%(152*UNIT),jaegerleicht);
			break;
		case 7:
			if(rand()%100<1)
				newenemy(0,rand()%(152*UNIT),bigbulleten);
			break;
		case 8:
			if(rand()%100<3)
				newenemy(0,rand()%(152*UNIT),bigbulleten);
			break;
		case 9:
			if(rand()%100<2)
				newenemy(0,rand()%(152*UNIT),normaleren);
			if(rand()%100<1)
				newenemy(0,rand()%(152*UNIT),bigbulleten);
			if(rand()%100<1)
				newenemy(30,rand()%(152*UNIT),strahlen);
			break;
		case 10:
			if(!exists(station))
				newenemy(0,rand()%(152*UNIT),station);

			break;
		}
			
	}
	for(e = enemylist; e < enemylist + maxenemy; e++)
		if(e->da)
			if(rand()%200<1&&e->et->bt >=0 && emp==0){
				if(e->t==strahlen){
					if(e->d==1){
						newbullet(e->x,e->y,1,5,0);
						e->d=0;
					}else
						e->d=1;
					continue;
				}
				newbullet(e->x, e->y, e->t==neutral?2:1,e->et->bt,0);
				if(e->t==station){
					newbullet(e->x,e->y+8*UNIT,1,e->et->bt,0);
					newbullet(e->x,e->y+16*UNIT,1,e->et->bt,0);
					newbullet(e->x,e->y+8*UNIT,1,e->et->bt,UNIT/2);
					newbullet(e->x,e->y+8*UNIT,1,e->et->bt,-UNIT/2);
					newbullet(e->x,e->y+8*UNIT,1,e->et->bt,UNIT);
					newbullet(e->x,e->y+8*UNIT,1,e->et->bt,-UNIT);
					newbullet(e->x,e->y+8*UNIT,1,e->et->bt,UNIT*6);
					newbullet(e->x,e->y+8*UNIT,1,e->et->bt,-UNIT*6);
				}
				if(e->t==neutral){
					newbullet(e->x,e->y,2,e->et->bt,UNIT/2);
					newbullet(e->x,e->y,2,e->et->bt,-UNIT/2);
					newbullet(e->x,e->y,2,e->et->bt,UNIT*6);
					newbullet(e->x,e->y,2,e->et->bt,-UNIT*6);
				}
			}
					
			
}
void
levelup(void)
{
	if(modus!=LEVEL)
		return;
	while(punkte>=levelpunkte[level]&&level<10){
		level++;
		if (level==10)
			if(!exists(station))
				newenemy(20*UNIT,80*UNIT,station);
		
	}
}