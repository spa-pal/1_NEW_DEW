DEBUG_GLOBAL equ 0


DEBUG_NMI equ (DEBUG_GLOBAL AND 0)
DEBUG_TRACE_LA equ (DEBUG_GLOBAL AND 0)
DEBUG_TRACE_INT equ (DEBUG_GLOBAL AND 0)
DEBUG_TRACE_SER equ (DEBUG_GLOBAL AND 0)

DEBUG115200 equ (DEBUG_GLOBAL AND 1)
DEBUG_DEBIO equ (DEBUG_GLOBAL AND 1)
DEBUG_STACK equ (DEBUG_GLOBAL AND 0)
DEBUG_NETBLK equ (DEBUG_GLOBAL AND 0)
DEBUG_NIC960 equ (DEBUG_GLOBAL AND 0)




DEBUG_INIT  macro 
IF DEBUG_NMI
    extrn _debug_init:near
    call  _debug_init
ENDIF      
endm

DEBUG_TRACE  macro stage, value
IF DEBUG_TRACE_LA OR DEBUG_TRACE_INT OR DEBUG_TRACE_SER
    extrn _debug_trace:near
    pushf
    push  value
    push  stage
    call  _debug_trace
    add    sp,4
    popf
ENDIF      
endm



