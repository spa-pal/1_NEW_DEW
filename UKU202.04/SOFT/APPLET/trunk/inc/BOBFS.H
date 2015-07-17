#pragma option -a-

struct bobfs_header_s
{
    WORD Signature;
    WORD Ident;
    DWORD DataLength;
    WORD Attributes;
    WORD Checksum;
    WORD var1;
    WORD var2;
};

extern int _pascal near flash_write(DWORD lina, void far * src, DWORD size);

int far _pascal bobfs_free(DWORD far * bytes_free);
int far _pascal bobfs_make(WORD Ident, DWORD DataLength, WORD options);
int far _pascal bobfs_write(WORD Ident, DWORD offset, void far * src, DWORD size);
int far _pascal bobfs_access(WORD Ident, void far * far * start, DWORD far * DataLength);
int far _pascal bobfs_kill(WORD Ident);
void far _pascal bobfs_setpar(DWORD start,DWORD end);

