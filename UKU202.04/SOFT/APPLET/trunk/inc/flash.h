/* * * * flash routines *new* * * * */

/* get flash type */
WORD flsh_typ(WORD ofs, WORD page);

/* clear flash page, address of page is parameter. offset ignored */
void flsh_clr(WORD ofs, WORD page);

/* program flash, even number of bytes necessary if 16-bit flash prom */
/* count must be 0 for 64k */
void flsh_pgm(WORD dstofs, WORD dstseg, WORD srcofs, WORD srcseg, WORD count);

/* 64k copy from 1000:0 to 8000:0 (code) */
void CopyEEPR(void);
