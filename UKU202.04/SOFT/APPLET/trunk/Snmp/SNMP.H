#define SNMPP   161

#define GETREQ  0xa0
#define GETNXT  0xa1
#define GETRESP 0xa2
#define SETREQ  0xa3
#define TRAP    0xa4

#define S_noError     0
#define S_tooBig      1
#define S_noSuchName  2
#define S_badValue    3
#define S_readOnly    4
#define S_genErr      5
#define S_NextEntry   6	/*JLJLJL*/

#define S_MAX_OBJLEN 32

#define IS_INT(asntyp) (asntyp == 2 || (asntyp >= 0x40 && asntyp <= 0x43))

struct snmp_context
{
   long intval;
   WORD stroff, strseg, strlen;
   BYTE *conarr[4], **conptr;
   WORD objid[S_MAX_OBJLEN+1], *objend;
   BYTE *hdrptr, *datptr, *inpptr, *inpend, *outptr;
   BYTE flags, asntyp;
};

#define FLAG_INCR 1
#define FLAG_PASS 2
#define FLAG_SET  8

#define S_SPAR(tbl) (tbl[0] & 1)
#define S_NOIX(tbl) (tbl[0] & 2)

#define S_TYP1(typ) (typ & 0x0007)
#define S_LEER   0x00
#define S_AFUN   0x01
#define S_SEQU   0x02
#define S_LEAF   0x03
#define S_TABL   0x04

#define S_TYP2(typ) (typ & 0x0030)
#define S_ROM    0x10
#define S_RAM    0x20
#define S_LFU    0x30

#define S_SET    0x40
#define S_LONG   0x80

#define S_OCTSTR (0x0000 + S_LEAF)
#define S_OBJECT (0x0100 + S_LEAF)
#define S_INT    (0x0200 + S_LEAF)
#define S_TIPADR (0x0300 + S_LEAF)
#define S_TCTR   (0x0400 + S_LEAF)
#define S_TGAUGE (0x0500 + S_LEAF)
#define S_TTICK  (0x0600 + S_LEAF)
#define S_PHADR  (0x0700 + S_LEAF)

extern BYTE fwbuf[];
#define outbuf fwbuf
#define outlim (fwbuf+500)
