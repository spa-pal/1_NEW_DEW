
/* memory functions */

void memcpy(void *to,const void *from,WORD len);
int memcmp(const void *to,const void *from,WORD len);
void memset(void *to,int val,WORD len);
void movedata(WORD fseg,WORD from,WORD tseg,WORD to,WORD len);

