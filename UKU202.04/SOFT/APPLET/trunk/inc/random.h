/* * * random generator prototypes * * */

#define rand() random(0)

WORD random(WORD);                /* get random number (unsigned) */

void srand(WORD);		/* set random seed */
