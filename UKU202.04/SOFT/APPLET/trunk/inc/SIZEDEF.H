#define VERS 100

#define TxEntrySize 80
#define MaxMsgSize  11+2+256+2+1
#define TxFifoSize 4
#define SndFifoSize 4

#if ((VERS==100) || (VERS == 50))
#define LoRxFifoSize 2048
#define LoTxFifoSize 2048
/*
#else
#define LoRxFifoSize 256
#define LoTxFifoSize 512
*/
#endif

#define CONQUMAX 32

#define WSTACK 64	/* worte stack fÅr watchprocess */
#define BSTACK 64	/* worte stack fÅr blinkprocess */
#define SSTACK 80	/* worte stack fÅr senderprocess */
#define CSTACK 80	/* worte stack fÅr channelprocess */
