/* * * * setjmp/longjmp prototypes * * * */

typedef struct { WORD si,di,bp,sp,ip; } jmp_buf;

int near setjmp(jmp_buf *jb);
void near longjmp(jmp_buf *jb, int rcode);