#include <gba.h>
#include <stdio.h>

typedef struct bullet bullet;
typedef struct enemy enemy;
typedef struct bullettype bullettype;
typedef struct enemytype enemytype;
typedef struct playertype playertype;
typedef struct item item;
struct bullet {
	u8 da;
	s16 x,y;
	u8 e;
	u8 t;
	bullettype *bt;
	s8 spy;
	
};
struct bullettype{
	s16 w,h;
	u16 bild;
	u8 sp;
	u16 eingefroren;
	u8 schaden;
};

struct enemy{
	u8 da;
	u8 t;
	enemytype *et;
	s16 x,y;
	s16 ghp;
	enemy *to,*from;
	u8 d;
	u8 schild;
};
struct enemytype{
	s16 w,h;
	u16 bild;
	u8 sp;
	s16 ghp;
	s8 bt;
	u8 size;
};
struct playertype{
	s16 w,h;
	u16 bild;
	u8 sp;
	s16 leben;
	s16 extraschaden;
};
struct item{
	s16 x,y;
	u8 da;
};
enum{
	maxbullets=64,
	maxenemy=48,
	nwaffen=3,
	maxitem=24,
};
extern bullet bulletlist[maxbullets];
extern enemy enemylist[maxenemy];
extern item itemlist[maxitem];
extern s16 px,py;
extern s16 leben;
extern int eingefroren;
extern u16 ammo[nwaffen];
extern playertype *pt;
extern int modus;
extern int punkte;
extern int level;
extern int itemwahr;
extern int itemspeed;
extern int emp;
enum{
NORMALERENT,
NTYPEN,
};
enum{
	PLAYER= 0 ,
	SCHUSS= 2 ,
	NORMALEREN=4,
	NORMSCHUSS=6,
	JAEGERSCHWER=8,
	JAEGERLEICHT=10,
	SCHNELLSCHUSS=12,
	LASEREN=14,
	HERZ=16,
	BIGBULLETEN=18,
	BIGBULLET=20,
	TODEN=22,
	MAUER=24,
	FROSTER=26,
	FROSTSCHUSS=28,
	ZAPFEN=30,
	BEAM=32,
	LASER=34,
	PLAYER1= 36,
	PLAYER2=38,
	PLAYER3=40,
	PLICE=42,
	SCHUETZER=44,
	SCHUETZ=46,
	PFEIL=48,
	ITEM=50,
	PLGLUECK=52,
	STATION=54,
	NEUTRAL=62,
	NEUTSCHUSS=66,
	ENSCHILD=68,
	STRAHLEN=70,
	STRAHL=72,
	STRAHLEN2=74,
	SCHNELLSCHUSSP=76,
	RAMEN=78,
	EMP=80,
};
enum{
	UNIT= 16,
};
enum{
	ARCADE,LEVEL,nmodus,
};
enum{
	normaleren,
	jaegerschwer,
	jaegerleicht,
	laseren,
	bigbulleten,
	toden,
	mauer,
	froster,
	beam,
	schuetzer,
	station,
	neutral,
	strahlen,
	entypen,
};
extern int killcount[entypen];
enum{
 ith=3,
 itw=3,
};
enum{
	ntype=6
};
enum{
	wtype=3
};
extern u8 freigeschaltet[ntype];