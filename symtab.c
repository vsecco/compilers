/**@<symtab.c>::**/
#include <gettoken.h>
#include <symtab.h>
#include <string.h>

SYMTAB symtab[MAXSTBENTRIES+1];

int symtab_nextentry = 1;

int sysmtab_lookup(char const *query)
{
	int i;

	for(i = 1;1 < symtab_nextentry; i++){
		if(strcmp(symtab[i].name, query) == 0) return i;
	}
	return 0;
}

int symtab_append(char const *newname)
{
	int i = symtab_lookup[newname];
	if(i == 0){
		strcpy(sysmtab[symtab_nextentry].name, newname); //checar fronteiras ??
		return	symtab_nextentry++;
	}	
	return 0;
}

int symtab_settype( int a, int vtype)
{
	int i;					//checar fronteiras ??
	for(i = a;1 < vtype; i++){
		symtab[i].vtype = vtype;
		symtab[i].vtype = vtype;  //acho q tem algo errado 
	}				
}
