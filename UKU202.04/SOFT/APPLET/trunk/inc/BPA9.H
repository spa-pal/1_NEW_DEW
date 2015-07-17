#define B_TMAX  61      /* max # Terminals in the group + server */
#define B_SEL   0x20    /* Select Bit in GID */
#define B_GMSK  0x1f    /* Adress Mask for GID */
#define B_DMSK  0x3f    /* Adress Mask for DID */

#define B_UNDEF 0
#define B_EOT   1
#define B_ACK0  2
#define B_ACK1  3
#define B_NAK   4
#define B_RVI   5
#define B_WACK  6
#define B_TTD   7
#define B_TOUT  8
#define B_GARB  9
#define B_OKDAT 10
#define B_ENQ   11
#define B_STX   12
#define B_POLL	13
#define	B_SELCT	14
#define B_CHKS	15

#define STX     0x02
#define ETX     0x03
#define EOT     0x04
#define ENQ     0x05
#define DLE     0x10
#define NAK     0x15
#define TOUT    -1
#define INTR    -2

#ifndef TRUE
#define TRUE	1
#endif

#define EOT_BEFORE_SELECT	0	/* set to 1 if EOT to send */