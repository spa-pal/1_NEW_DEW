
#if 0
#define xnice _BL=0,(*((void(far*_ss*)(void))(0x80)))
#define xkalloc _BL=1,(*((BYTE _ss *(far*_ss*)(WORD))(0x80)))
/*#define spawn _BL=2,(*((void pascal(far*_ss*)(void far*,WORD,void pascal(far*)(void)))(4*4))) */
#define xspawn _BL=2,(*((void (far*_ss*)(void (far*)(void),void _ss*,WORD,WORD,char far *))(0x80)))
#endif

void sdelay(WORD);
BYTE _ss * xkalloc(WORD);
void xspawn(void far *,void _ss *,WORD,WORD,char far *);
void putch(char);
void putstr(char *);
void puthex(WORD);

void xlmhnd();
DWORD xlmh();					/* set or find modules */

void far *pnorm(void far *);

#include <macros.h>

#define nice (*((void(far*_ss*)(void))(0x24*4)))

DWORD get_ticks(void);


