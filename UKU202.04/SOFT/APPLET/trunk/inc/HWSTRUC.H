
typedef struct hws {
    int cpu;            /* 0 for V.40, 0xffff for ES188 */
    int *iof[24];    /* jump table & status storage for serial modem control func */
    /* --------------------------------------- */
    int eeprom;         /* eeprom type 0: 93C46, 1: 24LC02,4,16 */
    int (*eewr)(BYTE *, WORD , WORD);
    int (*eerd)(BYTE *, WORD , WORD);
    BYTE cpuclk;         /* cpu clock in MHz, 10,20,25 */
    BYTE bussize;       /* bus size for flash etc, 8 or 16 bit */
    WORD page_size,fwe_start,fwu_start,rfw_pages,f_buf;
  	WORD web_start, web_pages, partialWebPages;
    BYTE max_ports;
    BYTE int_number;
} HWST;

extern HWST HW;          /* the standard structure */


/* Hardware dependent functions */
WORD HWSeries(void);
WORD HWSer(void);
WORD HWType(void);
WORD HWByte(void);
WORD HWOEM(void);
int  HW_ETH_NSel(void);
int  HW_ETH_NAuto(void);
int  HW_ETH_NBnc(void);
void HW_ETH_NSetIf(int);
void HWInit(int);
void HW_LED(WORD,int);
