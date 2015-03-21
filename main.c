#include "dat.h"
#include "fns.h"

playertype ptype[]={
//w,h,bild,sp,leben,extraschaden
	{8*UNIT,8*UNIT,PLAYER,UNIT,5,0},
	{6*UNIT,5*UNIT,PLAYER1,UNIT*2,3,0},
	{8*UNIT,8*UNIT,PLAYER2,UNIT/2,7,5},
	{7*UNIT,7*UNIT,PLAYER3,UNIT/2,15,3},
	{7*UNIT,7*UNIT,PLICE,UNIT,4,1},
	{8*UNIT,8*UNIT,PLGLUECK,UNIT,7,0},
};
int wbild[]={
	0,
	SCHNELLSCHUSSP,
	EMP,
};
bullet bulletlist[maxbullets];
enemy enemylist[maxenemy];
item itemlist[maxitem];
s16 leben;
u8 freigeschaltet[ntype];
void (*loop)(void);
int running;
int eingefroren;
int waffe;
u16 ammo[nwaffen];
playertype *pt;
int modus;
int punkte;
int level;
int itemwahr;
int itemspeed;
int killcount[entypen];
int emp;

s16 px,py,speed;
void 
eingabe(void)
{
	u16 k;
	static u16 ok;
	static u16 time;
	k=~REG_KEYINPUT;
	if(k&KEY_LEFT&& px>0)
		px-=speed;
	if(k&KEY_RIGHT&& px<231*UNIT)
		px+=speed;
	if(k&KEY_UP&&py >0)
		py-=speed;
	if(k&KEY_DOWN&&py <152*UNIT)
		py+=speed;
	if(k&KEY_B&&time==0&&(eingefroren==0|| pt==ptype+4)&& (waffe==0 || ammo[waffe]>0)){
		if(waffe==2){
			emp=180;
			time=340;
		}else{
			time=3;
			newbullet(px,py,0,waffe,0);
			if(pt==ptype+3){
				newbullet(px,py+7*UNIT/2,0,waffe,0);
				newbullet(px,py+7*UNIT,0,waffe,0);
			}
		}
		ammo[waffe]--;
	}
	if(k&KEY_L&&!(ok&KEY_L))
		waffe=(waffe+1)%3;
	if(time>0 )
		time--;
	if(eingefroren>0)
		eingefroren--;
	if(emp>0)
		emp--;
	ok=k;
}
void 
reset(void)
{
	enemy *e;
	bullet*b;
	
	for(b = bulletlist; b < bulletlist + maxbullets; b++)
			b->da=0;
	for(e = enemylist; e < enemylist + maxenemy; e++)
			e->da=0;
	leben=pt->leben;
	px=200*UNIT;
	py=80*UNIT;
	eingefroren=0;
	waffe=0;
	ammo[1]=500;
	ammo[2]=4;
	speed=pt->sp;
	level=0;
	punkte=0;
	if(modus==LEVEL)
		levelup();
	punkte=0;
	if(pt==ptype+5)
		itemwahr=100;
	else
		itemwahr=25;
	itemspeed=UNIT;
}

void
mainloop(void)
{
	bullet *b;
	enemy *e;
	item *it;
	int i,t;
	

	while(running){
		eingabe();
		movebullets();
		moveitem();
		treffer();
		moveenemy();
		spawn();
		VBlankIntrWait();
		iprintf(CON_CLS()); 
		objstart();
		if(leben>10){
			newobj(0,0,HERZ,0);
			iprintf("  %d",leben);
		}
		else
			for(i=0; i<leben; i++)
				newobj(i*10,0,HERZ,0);
		t=(eingefroren+59)/60;
		if(pt!=ptype+4)
			for(i=0; i<t; i++)
				newobj(100+i*10,0,ZAPFEN,0);
		iprintf("\nP %d",punkte);
		iprintf("\nL %d",level);
		iprintf("\nammo %d",ammo[waffe]);
		for(i=1;i<wtype;i++){
			if(i==waffe)
				newobj(40+12*i,11,RAMEN,0);
			newobj(40+12*i,11,wbild[i],0);
		}
		newobj(px/UNIT, py/UNIT, pt->bild, 0);
		for(b = bulletlist; b < bulletlist + maxbullets; b++)
			if(b->da){
				if(b->t==5) 
					for(i=b->x;i<240*UNIT;i+=8*UNIT)
						newobj(i/UNIT, b->y/UNIT, b->bt->bild, 0);
				else
					newobj(b->x/UNIT, b->y/UNIT, b->bt->bild, 0);
			}
		for(e = enemylist; e < enemylist + maxenemy; e++)
			if(e->da){
				if(e->t==strahlen)
					if(e->d==0)
						newobj(e->x/UNIT, e->y/UNIT,STRAHLEN, e->et->size);
					else
						newobj(e->x/UNIT, e->y/UNIT,STRAHLEN2, e->et->size);
					else
						newobj(e->x/UNIT, e->y/UNIT, e->et->bild, e->et->size);
				if(e->from!=NULL)
					newobjscal((e->x + e->et->w/2)/UNIT - 8, (e->y + e->et->h/2)/UNIT - 8, SCHUETZ, 0, 192 * 8 * UNIT / e->et->w, 192 * 8 * UNIT / e->et->h);
				if(e->schild>0)
					newobjscal((e->x + e->et->w/2)/UNIT - 8, (e->y + e->et->h/2)/UNIT - 8, ENSCHILD, 0, 192 * 8 * UNIT / e->et->w, 192 * 8 * UNIT / e->et->h);
			}
		for(it=itemlist;it<itemlist+maxitem;it++)
			if(it->da==1)
				newobj(it->x/UNIT,it->y/UNIT,ITEM,0);
		objend();
	}
}
void
missionerfuellt(void)
{
	if(killcount[jaegerleicht]>=30 && !freigeschaltet[1]){
		freigeschaltet[1]=1;
		save();
	}
	if(killcount[froster]>=50 && !freigeschaltet[4]){
		freigeschaltet[4]=1;
		save();
	}
	if(killcount[station]>=15&& !freigeschaltet[3]){
		freigeschaltet[3]=1;
		save();
	}
}
void
startloop(void)
{
	u16 k,ok;
	ok=0;
	int t,i;
	t=0;
	while(running){
		VBlankIntrWait();
		k=~REG_KEYINPUT;
		if(k&KEY_START&&freigeschaltet[t]==1){
			running=0;
			loop=mainloop;
			break;
		}
		if(ok&KEY_LEFT&&!(k&KEY_LEFT)){
			if(t==0)
				t=ntype-1;
			else
				t--;
		}
		if(ok&KEY_RIGHT&&!(k&KEY_RIGHT)){
			if(t==ntype-1)
				t=0;
			else
				t++;
		}
		ok=k;
		objstart();
		for(i=0;i<ntype;i++)
		newobj(30+20*i,i==t?100:120,ptype[i].bild,0);
		
		objend(); 
		rand();
	}
	pt=&ptype[t];
	reset();
}
void
modusloop(void)
{
	u16 k,ok;
	ok=0;
	int t;
	t=0;
	while(running){
		VBlankIntrWait();
		k=~REG_KEYINPUT;
		if(ok&KEY_START&&!(k&KEY_START)){
			running=0;
			loop=startloop;
			break;
		}
		iprintf(CON_CLS()"ACARDE \nLEVEL");
		if(ok&KEY_UP&&!(k&KEY_UP)){
			if(t==0)
				t=nmodus-1;
			else
				t--;
		}
		if(ok&KEY_DOWN&&!(k&KEY_DOWN)){
			if(t==nmodus-1)
				t=0;
			else
				t++;
		}
		objstart();
		newobj(100,10*t,PFEIL,0);
		objend();
		ok=k;
		
	}
	modus=t;
}
int
main()
{
	
	irqInit();
	irqEnable(IRQ_VBLANK);
	SetMode(LCDC_OFF);
	freigeschaltet[0]=1;
	consoleDemoInit();
	palinit();
	bildinit();
	REG_IME = 1;
	SetMode(MODE_0 | OBJ_ON | OBJ_1D_MAP | BG0_ON);
	loop=modusloop;
	pt=ptype;
	load();
	reset();
	for(;;){
		running=1;
		loop();
	}
}


u32
rand(void)
{
	static int w = 123, z = 456;
	
	z = 36969 * (z & 65535) + (z >> 16);
	w = 18000 * (w & 65535) + (w >> 16);
	return (z << 16) + w;
}


void
gameoverloop(void)
{
	u16 k,ok;
	ok=0;
	while(running){
		VBlankIntrWait();
		k=~REG_KEYINPUT;
		if(ok&KEY_START&&!(k&KEY_START)){
			running=0;
			loop=modusloop;
			reset();
		}
		ok=k;
	}
}
void
gameover(void)
{
running=0;
loop=gameoverloop;
}


