
int pascal r_open(BYTE far * file);
int pascal r_read(int handle, BYTE far * buffer, WORD len);
int pascal r_close(int handle);

#define NHANDLES 16

typedef struct
{
        /* source media */
        WORD media_type;   /*f.e. 0 for parallel flash, 1 - serial... */
        WORD flags;        /* reserved, need later maybe */
#define INUSE 0x0001       /* file is in use */
        DWORD f_start_pos; /* media pointer */
        DWORD f_curr_pos;  /* pointer in file */
        DWORD len;         /* # bytes in file */
} R_FILE;


