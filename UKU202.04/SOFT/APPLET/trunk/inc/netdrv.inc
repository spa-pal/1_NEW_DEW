DRV_IOCB struc
  portNum  dw ?
  NWTyp    dw ?
  STIME    dw ?
  lPortNum db ?
  SBFLAG   db ?
  SBufs0   dw ?
  SBufs1   dw ?    ; 2 Tx Bufs per network interface.
  dstrp    dw ?    ; DSTR *
  hw       dw ?    ; NET_HW_T *
  flags    db ?    ; Admin Status, Port Control
DRV_IOCB ends

MODE_BRIDGE_PASS_THRU   equ 07h
MODE_BRIDGE_PROXY_ARP   equ 0bh
MODE_WIRELESS_ONLY      equ 02h
MODE_WIRED_ONLY         equ 01h





