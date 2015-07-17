/**** Includes for UPNP ***/

/**** DEFINES for UPNP ***/
/** standard defines ***/
#define NUPO  10        /* max. # of objects to store/announce */
#define NANRQ 32        /* max. 32 pending requests for announcemts/ans */
#define NSUBS 16        /* can handle a max of 16 subscriptions */
#define NFUNC 16        /* number of functions supported */
#define NVARS 32        /* 32 variables alltogether for all services */
#define OK    1
#define DIRTY 0x0001    /* Dirtyflag for varibles */
#define LOCK  0x0001    /* Locking flag (semaphore) fo rservice */

/** Variable types ***/
#define UPNP_BOOLEAN    0   /* used as 1 BYTE (unsigned char) */
#define UPNP_INT        1   /* 2 byte signed int */
#define UPNP_STRING     2   /* unsigned char pointer */
#define UPNP_CHAR       3   /* 1 byte unsigned char */
#define UPNP_UI1		4	/* 1 byte unsigned char */
#define UPNP_UI2		5	/* 2 byte unsigned int */
#define UPNP_UI4		6	/* 4 byte unsigned long */
#define UPNP_I1 		7	/* 1 byte signed char */
#define UPNP_I2 		8	/* 2 byte signed int */
#define UPNP_I4 		9	/* 4 byte signed long */

							/*ak   below datatypes which UDS does not support now (now it's just string) */
							/*ak   added only for UPNP-compatibility and forwarding to attached device */

#define UPNP_R4 		10	/* 4 byte float */
#define UPNP_R8 		11	/* 8 byte float */
#define UPNP_NUMBER 	12	/* 8 byte float */
#define UPNP_FIXED_14_4 13	/* 8 byte float */
#define UPNP_FLOAT		14	/* 8 byte float */

#define UPNP_DATE		15	/* date in ISO 8601 format */
#define UPNP_DATETIME	16	/* date+time in ISO 8601 format */
#define UPNP_DATETIME_TZ 17	/* date+time+timezone in ISO 8601 format */
#define UPNP_TIME		18	/* time in ISO 8601 format */
#define UPNP_TIME_TZ	19	/* time+timezone in ISO 8601 format */

#define UPNP_BIN_BASE64	20	/* binary data in base64 (MIME) format */
#define UPNP_BIN_HEX	21	/* binary data in HEX format */

#define UPNP_URI		22	/* Universal Resource Identifier */
#define UPNP_UUID		22	/* Universally Unique Identifier */

/** states for upnp_shut the statevariable for UPNP machine **/
#define UPNP_SHUTDOWN   1   /* start the shutdown UPNP */
#define UPNP_DOWN       3   /* UPNP is down after state was set to 1 */


/* structures filled and alloced during startup of UPNP by parsing the XML file */
typedef struct UST {
  WORD etime;                       /* time remaining */
  WORD s;                           /* subscription enumerator */
  DWORD seq;                        /* sequence number */
  char cb[64];                      /* callback url */
} US_T;

typedef struct SUBSCRIPTION {
    US_T  far *stbl;               /* Subscription table */
    int   far (*sub_query)(US_T *);/* Upcall routine; has to be set by application; check if subscription is granted or not */
} UPNP_SUBT;

typedef struct VARIABLE { /*ak Changes of variable structure in reference with adding the range values (minimum, maximum, step) and new data types. */
  char        far *name;    /* name of variable, NOT zeroterminated !!! */
  union uval {
      unsigned char b;  /* ak boolean(0),char(3),ui1(4) */
	    signed char bt; /*ak i1(7) */
      unsigned int  ui; /*ak ui2(5) */
        signed int  i;  /*ak int(1),i2(8) */
	  unsigned long ul; /*ak ui4(6) */
		signed long l;  /*ak i4(9) */
	  unsigned char far *s; /* ak string(2),etc.(10...) */
  } value;
  union umax {
      unsigned char b;  /*ak boolean(0),char(3),ui1(4) */
	    signed char bt; /*ak i1(7) */
      unsigned int  ui; /*ak ui2(5) */
        signed int  i;  /*ak int(1),i2(8) */
	  unsigned long ul; /*ak ui4(6) */
		signed long l;  /*ak i4(9) */
	  unsigned char far *s; /*ak string(2),etc.(10...) */
  } val_max;
  union umin {
      unsigned char b;  /*ak boolean(0),char(3),ui1(4) */
	    signed char bt; /*ak i1(7) */
      unsigned int  ui; /*ak ui2(5) */
        signed int  i;  /*ak int(1),i2(8) */
	  unsigned long ul; /*ak ui4(6) */
		signed long l;  /*ak i4(9) */
	  unsigned char far *s; /*ak string(2),etc.(10...) */
  } val_min;
  union ustp {
      unsigned char b;  /*ak boolean(0),char(3),ui1(4) */
	    signed char bt; /*ak i1(7) */
      unsigned int  ui; /*ak ui2(5) */
        signed int  i;  /*ak int(1),i2(8) */
	  unsigned long ul; /*ak ui4(6) */
		signed long l;  /*ak i4(9) */
	  unsigned char far *s; /*ak string(2),etc.(10...) */
  } val_stp;
  WORD            type;     /* type of variable (0:bool,1:int,2:string, 3:char... see "(number)" above) */
  X_SECT          xs;       /* struct for information of this variable in XML-File like position and length of section */
  WORD            flags;    /* flags : 0x0001 = "dirty" that means variable has changed */
} UPNP_VAR;

typedef struct ARGUMENT { /*ak Adding the argument structure in reference with adding the new data types for functions with arguments. */
  char        far *name;    /* name of variable, NOT zeroterminated !!! */
  union uarg {
      unsigned char b;  /*ak boolean(0),char(3),ui1(4) */
	    signed char bt; /*ak i1(7) */
      unsigned int  ui; /*ak ui2(5) */
        signed int  i;  /*ak int(1),i2(8) */
	  unsigned long ul; /*ak ui4(6) */
		signed long l;  /*ak i4(9) */
	  unsigned char far *s; /*ak string(2),etc.(10...) */
  } value;
  WORD            type;     /* type of variable (0:bool,1:int,2:string, 3:char... see "(number)" above) */
  X_SECT          xs;       /* struct for information of this variable in XML-File like position and length of section */
/*ak  WORD            flags; */    /* flags : 0x0001 = "dirty" that means variable has changed */ /* ak Deleting "dirty" property for arguments, because all output arguments are sent always. */
  BYTE            dir;      /* /*ak direction of argument: in=0, out=1 */
} UPNP_ARG;

typedef struct ACTION {
    char      far *name;            /* name of action; NOT zeroterminated !!! */
    int       far (*Action)();      /* Action routine; has to be set by application */
    X_SECT    xs;                   /* struct for information of this variable in XML-File like position and length of section */
	UPNP_ARG  far *args;            /*Ak points to argument structure; build up during startup. Adding for function with arguments. */
} UPNP_ACT;

typedef struct SERVICE {
    char      far *id;          /* name of service; NOT zeroterminated !!! */
/* not yet supported for each service    UPNP_SUBT far *subt; */        /* points to subscription table; fixed size NSUBS */
    UPNP_ACT  far *acts;        /* points to actions table; build up during startup */
    UPNP_VAR  far *vars;        /* points to variable table; build up during startup */
    WORD          locked;       /* state of service TRUE is locked; False is UNLOCKED */
} UPNP_SRV;

typedef struct EMBDEVICE {
    char      far *name;        /* name of service; NOT zeroterminated !!! */
    UPNP_SRV  far *srv;         /* points to service table; build up during startup */
} UPNP_EMBDEV;

typedef struct ROOTDEVICE {
    char        far *name;      /* name of service; NOT zeroterminated !!! */
    UPNP_SRV    far *srv;       /* points to service table; build up during startup */
    UPNP_EMBDEV far *dev;       /* points to embedded device table; build up during startup */
} UPNP_RDEV;

/* protoypes for use of UPNP in application and internally */
int  upnp_init(WORD ms); /* simply blocks until UPNP is iniitalised during startup or error occured */
int  upnp_exit(WORD tp); /* simply blocks until UPNP is shut down or error occured */
void upnp_lock(UPNP_SRV far *srv);  /* Lock service prior to changes; lock only shortterm and unlock asap */
int  upnp_unlock(UPNP_SRV far *srv); /* Unlock service after changes; unlock asap after locking */
UPNP_SRV far *upnp_getservice(char far *devname, char far *srvname); /* get pointer to service strucutre within device; if srvs_name==NULL it returns the first service at all */
int  upnp_getvar(UPNP_SRV far *srv, char far *varname, void far *value); /* get variable of vars_name in Service srvs and put it in value */
int  upnp_getMMS(UPNP_SRV far *srv, char far *varname, void far *val_min, void far *val_max, void far *val_stp); /* get variable of vars_name in Service srvs and put it in values */
int  upnp_setvar(UPNP_SRV far *psrv, char far *varname, void far *value) ;/* set variable vars_name with value in Service srvs */
int  upnp_regfunc(UPNP_SRV far *srv, char far *actname, void (*func)()); /* register function handler in Service srv for action actname */
void upnp_regsubs(UPNP_SUBT far *srv, int far (*func)()); /* register function handler for subscription requests */
int  upnp_execfunc(UPNP_SRV far *srv, char far *actname, char far *buf); /* execute function in Service srv for action actname with parameter buf */
int upnp_getarg(UPNP_SRV far *psrv, char far *actname, char far *argname, void far *value); /*ak get value of argument arg_name for function act_name in Service srvs */
int upnp_setarg(UPNP_SRV far *psrv, char far *actname, char far *argname, void far *value); /*ak set value of argument arg_name for function act_name in Service srvs */

char *XmlGetArgStr(char *tag, char *buf); /*ak search {<"tag"...>arg</"tag">} in "buf" and return "arg" string */



/***********************************************************************/
/*** old stuff *********************************************************/
/***********************************************************************/

typedef struct UFT {
  char *name;
  int  (*f)();
} UF_T;

typedef struct UVT {
  char *name;
  WORD vtype;                   /* type of variable (0:bool,1:int,2:string, 3:char) */
  void *value;                  /* pointer to value */
  int  dirty;                   /* dirty flag */
} UV_T;


char far *XmlGetVal(char *buf,char *target,char far *src,
                    WORD bufsiz,WORD srcsiz,WORD wspok);

char *HdrGetVal(char *buf,char *target,char *src);

int upnp_ini(void);
int upnp_ctrl(WCT *w, char *path,char *hdr);
int upnp_sub(WCT *w,char *path,char *hdr);          /* subscribe */
int upnp_unsub(WCT *w,char *path,char *hdr);          /* subscribe */
void upnp_sev(US_T *);
void upnp_echk(void);
void upnp_qsv(char *,char *);
UF_T *upnp_rfunc(char *name, void (*func)());
UV_T *upnp_fvar(char *name);
int scanTags(BYTE *fname, BYTE *tag);
unsigned int fatoi(char far *p);

extern char far *upnp_rsc;         /* upnp resourcefile (name UPNP) start */
extern WORD upnp_rlen;             /* upnp resourcefile (name UPNP) start */

void upnp_commit(UPNP_SRV far *srv);   /* send event for service indicated, */
                                       /* if something changed */
