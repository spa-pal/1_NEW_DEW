  include ..\inc\debug\debug.inc
  
TCB struc
  Next_TCB_Ptr	dw	?
  Stack_Level	dw	?
  CCB_Ptr	dw	?
  Chan_Nr	dw	?
  Proc_Name	dw	?
  IO_Ptr	dw	?
  ProxyStack_ptr dw ?
IF DEBUG_STACK
  StackSize dw   ?
  tos       dw   ?
  shwm      dw   ?  
ENDIF
TCB ends
