#include "dat.h"
#include "fns.h"

int objp, matp;

void
objstart(void)
{
	objp = 0;
	matp = 0;
}

void
newobj(s16 x, s16 y, u16 chr, u16 sz)
{
	OAM[objp].attr0 = OBJ_Y(y) | OBJ_256_COLOR | OBJ_SHAPE(sz >> 2);
	OAM[objp].attr1 = OBJ_X(x) | OBJ_SIZE(sz & 3);
	OAM[objp].attr2 = OBJ_CHAR(chr);
	objp++;
}

void
newobjscal(s16 x, s16 y, u16 chr, u16 sz, s16 sx, s16 sy)
{
	OBJAFFINE *m;
	
	OAM[objp].attr0 = OBJ_Y(y) | OBJ_256_COLOR | OBJ_SHAPE(sz >> 2) | OBJ_ROT_SCALE_ON | OBJ_DOUBLE;
	OAM[objp].attr1 = OBJ_X(x) | OBJ_SIZE(sz & 3) | ATTR1_ROTDATA(matp);
	OAM[objp].attr2 = OBJ_CHAR(chr);
	
	m = &((OBJAFFINE*)OAM)[matp];
	m->pa = sx;
	m->pb = 0;
	m->pc = 0;
	m->pd = sy;
	objp++;
	matp++;
}

void
objend(void)
{
	int i;
	
	for(i = objp; i < 128; i++)
		OAM[i].attr0 = OBJ_DISABLE;
}
