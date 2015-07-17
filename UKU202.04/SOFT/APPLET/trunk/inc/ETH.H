typedef struct e_hdr {
  int len;	/* length */
  BYTE to[6];	/* to address */
  BYTE from[6];	/* from address */
  WORD type;	/* ethernet type, 0x800-IP 0x806-ARP */
} e_hdr_t;

struct arp_blk {
  BYTE to[6];
  BYTE from[6];
  WORD type;
  WORD hwtype;
  WORD proto;
  BYTE hwalen;
  BYTE pralen;
  WORD action;
  BYTE fromh[6];
  BYTE fromi[4];
  BYTE toh[6];
  BYTE toi[4];
};

typedef struct ate {
    BYTE ip[4];	/* IP Adresse  */
    BYTE hw[6]; /* HW Adresse  */
    WORD to;	/* Timeout val; 0--> Unused */
} ate_t;
