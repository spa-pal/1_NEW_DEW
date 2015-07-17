
WORD  FifoInit( BYTE*, int);
int   FlushIn( void);
BYTE  getch( void);
void  ungetch(BYTE);
int   pascal gethex8( BYTE*, BYTE *);
int   pascal getint( WORD*, WORD *);
int   pascal getint8( BYTE*, BYTE *);
void  pascal getip( BYTE*);
void  pascal getip2( BYTE*);
int   pascal getstr( char *buf, int len);
int   pascal getstrt( char *buf, int len);
char  pascal gethex(WORD *,WORD *);
int   pascal getynt( int);
int   pascal getyn( int);
int   InitLocalChan( void);
int   IOCall( int func, BYTE*, ...);
int   kbhit( void);
int   lio_cts( int);
int   lio_rts( void);
int   lio_dcd( int);
int   lio_dtr( void);
int   lio_tx(int);
int   LIOObuf(void);
int   LioBrk(void *);
int   OutBuf( void);
void  putcstn( int);
void  putcstr( int);
void  puthex( WORD, int);
void  putip( BYTE*);
void  putipd( BYTE*);
void  putint( WORD val, int width);
void  putvers( void);
void  putstr(char *);
void  puts(char *);
void  putyn(int);
void  putch(BYTE);
void  putcrlf(void);
void  d_putch(BYTE);
char  d_getch(void);
int   d_kbhit(void);
void  pascal d_putint(WORD,WORD);
void  d_putstr(char *);
//void  pascal d_puthex(WORD,int);
void d_puthex(WORD, int);

char *get_ips(char *,BYTE *);
char *get_int(char *,WORD *);

void putSPC(BYTE);

int printf(const char *,...);
int sprintf(char *,const char *,...);
int fprintf(WORD *,const char *,...);

