
typedef struct prs {
    int pass;           /* setup password pos in setup mem, if any */
    int plen;           /* password maxlen, if any */
    int gw;             /* setup offset for gateway */
    int nm;             /* setup offset for netmask */
    int tra;            /* token ring address, if any */
} PRST;
