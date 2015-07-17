/* ******************************************
   File IP.H

   Magic Numbers, Types and defines for Internet Protcols
*/


/* Defines for ARP - Address Resolution Protocol */

#define ARPTSize 32              /* maximum 32 Entries in ARP Table */
#define NUDPs 16		 /* max 16 udp ports */
/* #define NTCPs 8 */ /* max 8-16  tcp ports, defined by compile opt */

/* BYTE, WORD and DOUBLE swaps */

#ifndef ushort
#define ushort unsigned short
#endif
#ifndef ulong
#define ulong unsigned long
#endif

WORD gns(void *);
DWORD gnl(void *);

typedef struct a {
  BYTE ipa[4];                       /* IP address */
  BYTE hwa[6];                       /* HW address */
  BYTE sta;                          /* status byte */
#define STA_HW 1                     /* hw address set in struct */
#define STA_BC 2                     /* use broadcast to send block */
#define STA_SKPG 4                   /* skip gateway check (complete) */
#define STA_TCP 8                    /* TCP (disallow mcst/bcst) */
#define TTL_LOCAL 16                 /* set if TTL should be set to one */
#define STA_TAKE 32                  /* take the ip/hw as it is set up,
                                        no lookup, no resolve */
#define STA_INTF 64                  /* Use the interface for outbound as indicated in portNum */
  int portNum;
} AD_T;

typedef struct i {
  BYTE taken;                   /* !=0 if arp discovers same ip */
  BYTE type;                    /* Type of interface. */
#define IP_INTF_WIRED_ETHERNET      0x01
#define IP_INTF_WIRELESS_ETHERNET   0x02
  WORD intf;                    /* interface number for this ip subnet. */
  BYTE addr[4];                 /* IP address of CoBox */
  BYTE nmsk[4];                 /* netmask (calculated) */
  BYTE gway[4];                 /* default gateway ip address */
  BYTE ns[4];                   /* default name server */
  BYTE bcst[4];                 /* broadcast address (calculated) */
  WORD id;                      /* block identification */
  WORD arpcachetime;            /* time (seconds) for keeping arpentry cached */
  AD_T a;                       /* address entry for ip checks
                                   will contain assigned IP address */
} IP_T;
extern IP_T ip;

#define ntohs(x) ((((ushort)x)>>8)|(((ushort)x)<<8))

//#define ntohl(x) ( (((ulong)ntohs(x))<<16) | ((ulong)ntohs(((ulong)x)>>16)) )
#define ntohl(x) ( (((x) & 0xff000000) >> 24) |  (((x) & \
0x00ff0000) >>  8) |  (((x) & 0x0000ff00) <<  8) |  (((x) & 0x000000ff) << 24)  )

#define htons(x) ntohs(x)

#define htonl(x) ntohl(x)

#define intohs(x) x
#define intohl(x) x

/* * * * Low IP Prototypes * * */
AD_T *hw_resolve(AD_T *);         /* resolve IP address to AD_T structure */

DWORD dns_resolve(char *);        /* resolve hostname, return 0.0.0.0 if error */
