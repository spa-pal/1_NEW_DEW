	.186
;	      include ..\kernel\HARDWARE.INC
        include ..\inc\sys\segdef.inc
        
        
BANK0 equ 00300h
;BANK1 equ 081h        
BANK1 equ 00200h        
BANK2 equ 08200h        

_EXTDATA segment
        extrn   Orig_off:word
        extrn   Orig_seg:word
        extrn   Orig_sp:word
        extrn   Orig_stack:word
        extrn   flags:word
IFDEF  CENTRAL_PROXY
        extrn   Func_addr:word
ELSE
ENDIF
_EXTDATA ends

    IFDEF  CENTRAL_PROXY
I_Func_m macro  I_Func_lbl, Func, Bank
        public I_Func_lbl
I_Func_lbl:
        pushf
        cli
        pop     [flags]
        mov     word ptr [Func_addr], offset Func
        push    cs
        push    Bank
	      jmp	    far proxy
endm        
    ELSE
I_Func_m macro  I_Func_lbl, F_addr, F_Bank, F_Proxy_ret, F_Bank_name
        IFNDEF F_addr
        extrn   F_addr:far
        ENDIF
        public  I_Func_lbl
I_Func_lbl:
        pushf
        cli
        pop     DGROUP:[flags]
        pop	    DGROUP:[Orig_off]
        xchg	  sp,DGROUP:[Orig_sp]
        push	  cs
        push	  DGROUP:[Orig_off]
        xchg	  sp,DGROUP:[Orig_sp]
	      push	  offset F_Proxy_ret    ; All need to be at same location
        push    DGROUP:[flags]
        push    F_Bank
;        push    offset F_addr
        push    offset F_Bank_name:F_addr
        iret

endm        
    ENDIF        
        

  
Proxy_ret_m macro Proxy_ret_lbl
public Proxy_ret_lbl
Proxy_ret_lbl:
        pushf
        cli
        xchg	  sp,word ptr DGROUP:[Orig_sp]
        pop     word ptr DGROUP:[Orig_off]
        pop     word ptr DGROUP:[Orig_seg]
        xchg    sp,word ptr DGROUP:[Orig_sp]
        push	  word ptr DGROUP:[Orig_seg]
        push	  word ptr DGROUP:[Orig_Off]
        iret
endm
  
