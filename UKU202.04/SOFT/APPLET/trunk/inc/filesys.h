/***************************************/
/* new universal file system for COBOS */
/***************************************/

/* suggestion and main ideas -- Johannes Rietschel */
/* this realization for parallel and serial flash -- ak */

int   r_open(BYTE far * file); /* opens file */
                               /* parameter: pointer to name of file */
                               /* returns:   "handle" index in R_FILE table */
                               /*            or -1 if file is not found */

int   r_close(int handle);     /* close file: drops flag INUSE in RFILE table */

WORD  r_read(int handle, BYTE far * buffer, WORD len); /* reads opened file from current position */
                               /* parameter: "handle" index for given file */
                               /*            pointer to external "buffer" for saving data */
                               /*            amount of demanded data, <= sizeof(buffer) */
                               /* returns:   real amount of read data (including 0) */
                               /*            or -1 if error */

/* additional functions for controlling, all returns 0 if OK, or -1 if error */
DWORD get_file_start_pos(int handle); /* returns file start position from R_FILE table */
DWORD get_file_len(int handle);       /* returns file length from R_FILE table */
DWORD get_file_curr_pos(int handle);  /* returns current position from R_FILE table (from file begining) */
int   set_file_curr_pos(int handle, DWORD offset); /* changes current position into R_FILE table */

#define NHANDLES 16

typedef struct
{
        WORD media_type;   /* f.e. 0 for parallel flash, 1 - serial... */
        WORD flags;        /* reserved, need later maybe */
#define INUSE 0x0001       /* file is in use */
        DWORD f_start_pos; /* media pointer (file begining from 0 position of given media) */
        DWORD f_curr_pos;  /* pointer in file (from file begining) */
        DWORD len;         /* # bytes in file */
} R_FILE;

BYTE far *FWFile(BYTE *f,WORD *rlen, int *status);
        /* general purpose file find, used to find a file
           or resource in the flash space.
           returns NULL pointer and length of 0 if not found,
           pointer to first byte of file/resource, plus
           length in 2nd parameter otherwise NOT case sensitive.
           uses HW.f_xxx to determine where to search.
         */

