typedef struct tt{
  void (*f)(struct tt *);
  WORD t,tval;
} TTStruc;

int r_times(PTF,WORD);
int r_timems(PTF,WORD);

void InitialiseTime(WORD);              /* startup, called only once by kernel */
