/* XML functions */

#ifndef XML_DEFS

#define XML_DEFS

typedef struct XSECT {
  char far *xp;
  WORD xl;
} X_SECT;


int XMLGetSection(X_SECT *p,char *name);        /* get xml section,tag is w/o <> */
                                                /* this drills in up to variables */

int XMLGetAttrib(X_SECT *p,char *name);         /* this brings back a ptr to */
                                                /* the beginning of attribute "name" */
                                                /* or 0 if no such attribute */
int XMLGetContents(X_SECT *p);                  /* get pointer to first char of */
                                                /* variable content, basically */
                                                /* skips tag - nothing else */

int XMLRetrieveVariable(char far *p,void *v,int type);
                                                /* parse variable into buffer v */


/* helper functions */
char far * _fstrnchr(char far *p,WORD l,BYTE val);      /* find occurence of char */
                                                        /* limited by len l */


/* return values in general: 0 for ok, 1... for error code */
/* variable types: */

#define XML_BOOL 0
#define XML_INT 1
#define XML_STRING 2
#define XML_CHAR 3

#endif

