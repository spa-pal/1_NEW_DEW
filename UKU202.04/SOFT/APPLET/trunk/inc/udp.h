
/* * * * * UDP functions * * * * */
void udp_register(WORD port,PTF fct);
int udp_reregister(WORD port,PTF fct);
int udp_send(BYTE *adr,WORD dp,WORD sp,void *buf,int len);
int udp_sehw(AD_T *adr,WORD dp,WORD sp,void *buf,int len);

