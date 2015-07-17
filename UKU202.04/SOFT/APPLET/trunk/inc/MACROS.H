#if __STDC__
#define _Cdecl
#else
#define _Cdecl	cdecl
#endif


	/* These are in-line functions.  These prototypes just clean up
	   some syntax checks and code generation.
	 */

#if 0

void	_Cdecl	__cli__		(void);
void	_Cdecl	__sti__		(void);
unsigned char _Cdecl __inportb__(unsigned portid);
void	_Cdecl	__outportb__	(unsigned portid, unsigned char value);
void	_Cdecl	__int__		(int interruptnum);

#define disable()	__cli__()		/* Clear interrupt flag */
#define enable()	__sti__()		/* Set interrupt flag */
/*#define inportb(portid) __inportb__(portid) */	/* Byte IN instruction */
/*#define outportb(portid, v) __outportb__(portid,v) */ /* Byte OUT instruction */

#define inportb(__portid)           __inportb__(__portid)
#define outportb(__portid, __value) ((void) __outportb__(__portid, __value))
#define inport(__portid)            __inportw__(__portid)
#define outport(__portid, __value)  ((void) __outportw__(__portid, __value))

#else
void    _Cdecl  __int__         (int interruptnum);
#define enable() asm sti
//#define disable() asm cli
//#define disable()    asm cli; asm jmp label; label:      // EX bug executes instruction in  pipeline after CLI before disabling interrupts
#define disable()    asm cli; asm dw 0x00EB      // jump short $+2  already assembled
 
unsigned char _Cdecl __inportb__(unsigned portid);
unsigned      _Cdecl __inportw__(unsigned portid);

unsigned char _Cdecl __outportb__(unsigned portid,unsigned char v);
unsigned      _Cdecl __outportw__(unsigned portid,unsigned v);
#define geninterrupt(i) __int__(i)              /* Interrupt instruction */
/*#define inportb(pi) asm { mov dx,pi; in ax,dx; } */
#define inportb(__portid)           __inportb__(__portid)
#define inport(__portid)           __inportw__(__portid)
#define outportb(__portid,__value) __outportb__(__portid,__value)/* Byte OUT instruction */
#define outport(__portid,__value) __outportw__(__portid,__value)/* WORD OUT instruction */

/*#define outportb(pi,v) asm { mov dx,pi; mov al,v; out dx,al; } */
/*#define outport(pi,v) asm { mov dx,pi; mov ax,v; out dx,ax; } */
#endif


/* some other compilers use inp, outp for inportb, outportb */
#define inp(portid)	  inportb(portid)
#define outp(portid,v)	  outportb(portid,v)
#define InByte(portid)    inportb(portid)
#define OutByte(portid,v) outportb(portid,v)
#define DisableInterrupts() disable()
#define EnableInterrupts() enable()

#define MK_FP(seg,ofs)	((void far *) \
			   (((unsigned long)(seg) << 16) | (unsigned)(ofs)))
#define MK_FP2(adr)	((void far *) \
			   (((adr & 0xff0000) << 8) | (adr & 0xffff)))
#define FP_SEG(ptr)	((unsigned)(((unsigned long)ptr)>>16))
#define FP_OFF(ptr)	((unsigned)ptr)

#if 1
#define poke(a,b,c)	(*((unsigned  far*)MK_FP((a),(b))) = (int)(c))
#define pokeb(a,b,c)	(*((unsigned char far*)MK_FP((a),(b))) = (char)(c))
#define peek(a,b)	(*((unsigned  far*)MK_FP((a),(b))))
#define peekb(a,b)	(*((unsigned char far*)MK_FP((a),(b))))
#else
#define peek(seg,ofs) asm { mov ax,seg; mov es,ax; mov bx,ofs; mov ax,es:[bx]; }
#define peekb(seg,ofs) asm { mov ax,seg; mov es,ax; mov bx,ofs; mov al,es:[bx]; }
#define poke(seg,ofs,val) asm { mov ax,val; mov bx,seg; mov es,bx; mov bx,ofs; mov es:[bx],ax; }
#define pokeb(seg,ofs,val) asm { mov al,val; mov bx,seg; mov es,bx; mov bx,ofs; mov es:[bx],ax; }
#endif

#define PeekByte(a,b)     peekb(a,b)
#define PokeByte(a,b,c)   pokeb(a,b,c)
#define PeekWord(a,b)     peek(a,b)
#define PokeWord(a,b,c)   poke(a,b,c)
