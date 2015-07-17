

void pascal dio_vector_init(DWORD,DWORD,DWORD);
DWORD pascal dio_vector_read(void);

void pascal dio_bit_set(WORD bit);
void pascal dio_bit_reset(WORD bit);
void pascal dio_bit_setres(WORD bit,WORD val);
int pascal dio_bit_read(WORD bit);
void pascal dio_bit_out(WORD bit,WORD val);
void pascal dio_bit_in(WORD bit);

void pascal dio_vbit_set(WORD vbit);
void pascal dio_vbit_reset(WORD vbit);
void pascal dio_vbit_setres(WORD vbit,WORD val);
int pascal dio_vbit_read(WORD vbit);
void pascal dio_vbit_out(WORD vbit,WORD val);
void pascal dio_vbit_in(WORD vbit);

void pascal dio_vbit_init(void);

#ifndef NIOBITS
#define NIOBITS 32              /* default */
#endif


typedef struct {
  WORD size;                    /* 64 in this release, could be increased */
  WORD bit[NIOBITS];
} DIO_S;

#define DIO_INV 0x40
#define DIO_NONE 0
#define DIO_ACT 0x80                    /* active - existing. don't execute */
#define DIO_OUTPUT 0x8000    /* is an output (mainly for init) */
#define DIO_INIACT 0x4000    /* set it active at init */

                                        /* any function on this bit otherwise */
#define LEDR 0                          /* RED led */
#define LEDG 1                          /* GREEN led */
#define LEDY 2                          /* YELLOW led */
#define I2CC 3                          /* I2C Clock pin */
#define I2CD 4                          /* I2C Data pin */
#define RTSA 5                          /* RTS channel a */
#define CTSA 6                          /* CTS channel a */
#define DTRA 7                          /* DTR channel a */
#define DCDA 8                          /* DCD channel a */
#define RVAA 9                          /* 232/485 selection channel a */
#define TXOFFA 10                       /* "transmitter off" channel a */
#define RTSB 11
#define CTSB 12
#define DTRB 13
#define DCDB 14
#define RVAB 15
#define TXOFFB 16
#define RESBUT 17                       /* "reset" button (soft reset) */
#define RS485_SEL 18                    /* 232/485 selection (wiport/wibox/nanobox) */
#define RS485_2W 19                     /* RS485 2 Wire Mode Selection */
#define TRIG1 20
#define TRIG2 21
#define TRIG3 22
#define DEFAULT 23                      /* reset to defaults - select wireless interface (in WiPort) */
#define RS485_4W 24                     /* RS485 4-wire mode selection (inverse of 2W) */
#define DEFAULT_ETH 25                  /* reset to defaults - select wired interface (in WiPort). */
#define RS485_SEL_A 26					/* 232/485 selection (UDS2100) */
#define RS485_2W_A 27					/* RS485 2 Wire Mode Selection (UDS2100) */
#define LINK 		    28					/* link index to DIO.bit[] */


typedef struct
{
	BYTE	bIndex;
	BYTE	bPhyPin;
	WORD	wSetting;
}CPStruct;

#define NOT_LINK		0x00				// must be different from CPx_PIOPIN


/* user application defined bits should start at 32. */

