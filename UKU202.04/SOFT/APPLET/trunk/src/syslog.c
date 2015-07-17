#include <style.h>
#include <globals.h>
#include <io.h>
#include <ip.h>
#include <string.h>
#include <udp.h>
#include "syslog.h"
#ifdef SNTP
#include <smsgw.h>
extern  BYTE SNTPStatus;
extern  DWORD ntime;
extern  WORD ti_secs;
static	BYTE ntpbuf[64];
static  BYTE month[13][4]={"xxx","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
#endif

unsigned long LOGSRV1 = 172L + (19L << 8) + (215L << 16) + (5L << 24);
unsigned long LOGSRV2 = 0L + (0L << 8) + (0L << 16) + (0L << 24);

#define LOGMESSAGELEN 120
static	BYTE sendbuf[LOGMESSAGELEN];
static byte lock = 0;

/**********************************************************************/
/* Procedure syslog.                                                  */
/**********************************************************************/
void syslog(WORD pcode, BYTE *message) {
	BYTE *sltmp;
	WORD offset,i;
	DWORD ctime;

	while(lock) nice();
	lock = 1;

	if(!LOGSRV1 && !LOGSRV2) {
		lock = 0;
		return;
	}

	sprintf(sendbuf, "<%5d> ", pcode);

#ifdef SNTP
	if(SNTPStatus) {
		disable();
		ctime = ntime + ti_secs;
		enable();
		akttimex(ntpbuf, ctime);
		memcpy(sendbuf + 7, month[atoi(ntpbuf + 12)], 3); /* month */
		sendbuf[10] = ' ';
		memcpy(sendbuf + 11, ntpbuf + 9, 2); /*day of month*/
		sendbuf[13] = ' ';
		memcpy(sendbuf + 14, ntpbuf, 8);  /*hh:mm:ss*/
		sendbuf[22] = ' ';
		/* cat SMTPMSG until '.' */
		offset = 23; i = 0;
		while(SMTPMSG[i] && SMTPMSG[i] != '.') {
			sendbuf[offset++] = SMTPMSG[i++];
		}
		sendbuf[offset++] = ':';
		sendbuf[offset++] = ';';
		sendbuf[offset++] = ' ';
		sendbuf[offset] = 0;
	}
	else {
#endif
		offset = 8;
#ifdef SNTP
	}
#endif

	if(strlen(message) > (LOGMESSAGELEN - offset - 1))
		message[LOGMESSAGELEN - offset] = 0;
	strcat(sendbuf, message);

printf("Log message: %s\r\n", message);

	if(LOGSRV1)
		udp_send((BYTE *)&LOGSRV1, SYSLOG_PORT, SYSLOG_PORT, sendbuf, strlen(sendbuf));
	if(LOGSRV2)
		udp_send((BYTE *)&LOGSRV2, SYSLOG_PORT, SYSLOG_PORT, sendbuf, strlen(sendbuf));

	lock = 0;
}
