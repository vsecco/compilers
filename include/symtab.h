/**@<symtab.h>::**/

#include <gettoken.h>
#define MAXSTBENTRIES 0x1000
typedef struct {
	char name[MAXSTRLEN+1];
	int vtype;
}SYMTAB

extern SYMTAB symtab[];

int sysmtab_lookup(char const *query);

int symtab_append(char const *newname);

int symtab_settype(int, int);

