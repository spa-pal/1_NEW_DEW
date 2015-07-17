typedef struct {
  char *Title;
  char *Unit;
  WORD LowestIndex;
  WORD HighestIndex;
  char *Options[];
} SelectionList_t;

#define SelectionList_t_defined

void print_allowed(int low, int high);
WORD SelectFromRange(char *List, BYTE LowestAllowed, BYTE HighestAllowed, WORD CurSel);
WORD SelectFromList(SelectionList_t *List, WORD StoredSel);
void ShowFromList(SelectionList_t *List, WORD StoredSel);
void putcst_pde(int str_const, BYTE flag);

