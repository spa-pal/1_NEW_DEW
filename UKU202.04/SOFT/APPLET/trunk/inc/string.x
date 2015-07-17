/* * * * string functions * * */

int strcmp(char *to,char *from);
char *strchr(char *from,char what);
int strncmp(char *to,char *from,unsigned count);
void strcpy(char *to,char *from);
int strlen(char *s);

/* ... and memory functions */

void memcpy(void *to,const void *from,WORD len);
int memcmp(const void *to,const void *from,WORD len);
void memset(void *to,int val,WORD len);
void movedata(WORD fseg,WORD from,WORD tseg,WORD to,WORD len);


