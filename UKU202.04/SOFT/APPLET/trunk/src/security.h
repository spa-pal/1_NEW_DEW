#define SECFLAGS   	(Setup[122])
#define ENHPASSWD   (SECFLAGS&0x08)
#define DISTELNET   (SECFLAGS&0x01)
#define DISTFTP     (SECFLAGS&0x02)
#define DIS77FE     (SECFLAGS&0x10)
#define DISWEBS     (SECFLAGS&0x20)
#define DISSNMP     (SECFLAGS&0x40)
#define SECFLAGS2   (Setup[170])/* Security flags 2 */
#define DISECHO     (SECFLAGS2&0x01)
#define DIS77F0     (SECFLAGS2&0x02)
#define DISCGIS     (SECFLAGS2&0x80)
#define P_ENHPWD    (&Setup[139])
#define P_SNMPCOM   (&Setup[156])

