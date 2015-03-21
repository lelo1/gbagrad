#include "dat.h"
#include "fns.h"

enum { SAVESIZE = ntype };

static u8 buf[SAVESIZE];
static const u32 magic[] = {0x4d415253, 0x6e6e565f, 0x6e};

u16
checksum(u8* p, u8 c)
{
	u16 s0, s1;
	
	s0 = 0;
	s1 = 0;
	while(c--){
		s0 = (s0 + *p++) % 255;
		s1 = (s0 + s1) % 255;
	}
	return s1 << 8 | s0;
}

void
cpy(u8* dst, u8* src, int c)
{
	while(c--)
		*dst++ = *src++;
}

void
load(void)
{
	u16 c;

	cpy(buf, (u8*) SRAM, SAVESIZE + 2);
	c = checksum(buf + 2, SAVESIZE);
	if(c != (buf[0] | buf[1] << 8))
		return;

	cpy(freigeschaltet, buf + 2, ntype);
}

void
save(void)
{
	u16 c;

	cpy(buf + 2, freigeschaltet, ntype);
	c = checksum(buf + 2, SAVESIZE);
	buf[0] = c;
	buf[1] = c >> 8;
	cpy((u8*)SRAM, buf, SAVESIZE + 2);
}
