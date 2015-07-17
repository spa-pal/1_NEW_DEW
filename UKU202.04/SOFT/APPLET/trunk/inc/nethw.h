/* ******************************************
   File nethw.h

   Struct which holds various network-hw specific variables
   18.07.02 jb C-020325-16212 16 chr DHCP name
*/

/* Matches the first 11 entries of the S_vars table which represent variables for
   for the ifTable
 */
#ifndef NET_HW_INC
#define NET_HW_INC

struct ifTabSNMP {
  DWORD speed;
  DWORD inOctets;
  DWORD inUnicasts;
  DWORD inBroadcasts;
  DWORD inDiscards;
  DWORD inError;
  DWORD inUnknownProto;
  DWORD outOctets;
  DWORD outUnicasts;
  DWORD outBroadcasts;
  DWORD outDiscards;
} ;

typedef struct h {
  BYTE hw_addr[6];              /* hardware address */
  WORD Net_HW_Typ;              /* network type, 1 for eth, 6 token ring */
                                /* THE FOLLOWING VARS MUST BE KEPT IN THEIR
                                   RELATIVE POSITIONS DUE TO ASSEMBLER
                                   PARTS */
  WORD TRiS;                    /* token ring insertion state */
  BYTE trsa,trnorif,TRSpeed;    /* token ring specific variables */
  BYTE DHName[17];               /* max. 7 character, ends with 0 character */
  WORD portNum;
  struct ifTabSNMP *ifstats;    /* pointer to storage of SNMP variables. */
} NET_HW_T;                     /* network hardware variables */

extern NET_HW_T nethw;          /* the standard structure */

extern BYTE * GetSendBuf(WORD);
extern void   FreeSendBuf(BYTE *);
extern int    _send_block(BYTE *,WORD, WORD);    /* buf, len, interface */
//extern int    IPFake(BYTE *,WORD,WORD);         /* simulate incoming packet */


/*
   Structure to hold information about the network interfaces
   in a product
 */
typedef struct net_intf_t
{
   WORD type;                 /* Type of network interface (eg. ND, NW) */
   BYTE count;                /* Number of network interfaces of 'type' */
} net_intf;

#endif
