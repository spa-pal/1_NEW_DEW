#ifndef DEBUG_H
#include <debug\debug.h>
#endif

typedef struct TCB {
   struct TCB *NextTCB;     // 0
   WORD *StackLevel;         // 2
   CCB *CCB_Ptr;            // 4
   int Chan_Nr;             // 6
   char *Proc_Name;         // 8
   WORD *IO_Ptr;            // 10
   WORD *ProxyStack_ptr;
#if DEBUG_STACK
   WORD StackSize;           // usable stack size
   WORD *tos;                //pointer to top of stack   
   WORD shwm;                // stack high water mark
#endif
   } TCB;
