#include "dat.h"
#include "fns.h"

void
palinit()
{
	u16 *p;
	
	p = BG_COLORS;
	p[0] = RGB5(0, 0, 0);
	p = OBJ_COLORS;
	// Rot
	p[1] = RGB5(31, 0, 0);
	// Grün
	p[2] = RGB5(0, 31, 0);
	// blau
	p[3] = RGB5(0, 0, 31);
	// gelb
	p[4] = RGB5(31,31, 0);
	// türkis
	p[5] = RGB5( 0,31,31);
	// violett
	p[6] = RGB5(31, 0,31);
	// magenta
	p[7] = RGB5(31,16,31);
	//hell rothell
	p[8] = RGB5(31,16,16);
	//hell grünhell
	p[9] = RGB5(16,31,16);
	//hell blauhell
	p[10] = RGB5(16,16,31);
	//weiß
	p[11]= RGB5(31,31,31);
	//superhellblau
	p[12]= RGB5(24,24,31);
	//grau
	p[13]= RGB5( 8, 8, 8);
	//hellgrau
	p[14]= RGB5(24,24,24);
}

