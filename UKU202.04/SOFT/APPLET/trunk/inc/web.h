#define IBSIZE 512
#define OBSIZE 256


typedef struct WC_T {
  BYTE InBuf[IBSIZE+8];
  BYTE OutBuf[OBSIZE+8];
  char *hbuf;               /* header buffer, will be assigned dynamical */
  TCP_t *t;
  WORD status;
#define WEB_STAT_CONNECT    0x0001   /* set when connected and cleared on disconnect */
} WCT;

void WebProcess(void);          /* web process, can be started multiple times */
                                /* runs on port 80 so far ... */

int WebMethRegister(char *meth,int (*f)(),char *path);
                                /* register web method like PUT, GET, NOTIFY
                                   function f will be called if method is matched
                                   path can be NULL, which means that all URLs
                                   are accepted, if path is given, the method
                                   is called only for this specific path.
                                   this can be used to have specific gets for
                                   specific purposes.
                                   used in get.c to register the dynamic contents
                                   get to the path "./d"
                                */

BYTE far *FWFile(BYTE *f,WORD *rlen, int *status);
                                /* general purpose file find, used to find a file
                                   or resource in the flash space.
                                   returns NULL pointer and length of 0 if not found,
                                   pointer to first byte of file/resource, plus
                                   length in 2nd parameter otherwise
                                   NOT case sensitive.
                                   uses HW.f_xxx to determine where to search.
                                */

WORD wWriteOutput(TCP_t *t, BYTE far *buf, WORD len, WORD *fifo);

stdget(WCT *w, char *file, char *hdr);
                                /* std get method, supporting dynamic contents as
                                   well as static, standard.
                                   will generate header, and will take the
                                   file "file" from the flash using FWFile
                                */

stdgetEx(WCT *w, char *file, char *hdr, char *cType, DWORD cLen);




