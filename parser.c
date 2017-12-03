/**@<parser.c>::**/

#include <stdlib.h>
#include <stdio.h>
#include <gettoken.h>
#include <keywords.h>
#include <dtypes.h>
#include <symtab.h>
#include <parser.h>
#include <string.h>
int             lookahead;



int varlist(void)
{
	/**/int a = symtab_nextentry;/**/
VAR_LIST:
	/**/if( symtab_append(lexeme) == 0){
		fprintf(stderr,
		"fatal error: %s already declared\n",lexeme);
	}/**/
	match(ID);
	if(lookahead == ','){
		match(','); goto VAR_LIST;
	}
	return a;
}

int vartype(void)
{
	int type = lookahead;
	switch(lookahead){
		case BYTE:
		case WORD:
		case INTEGER:
		case LONGINT:
		case REAL:
		case DOUBLE:
		case BOOLEAN:
		case CHAR:
			match(lookahead);
			break;
		default: match(STRING);	
	}
	return type;
}

void declarative (void)
{
	/**/int range_start, range_type;/**/
	//vardcl -> VAR varlist : vartype;
	//varlist -> ID { , ID }
	//vartype -> BYTE | WORD | INTEGER | LONGINT | REAL | DOUBLE | BOOLEAN | CHAR | STRING
	if (lookahead == VAR){
		match(VAR);
WHLID:
		range_start = varlist();
		match(':');
		range_type = vartype();
		match(';');
		/**/symtab_settype(range_start, range_type)
		if(lookahead == ID) goto WHLID;
	}
}

void stmt (void)
{
	/**/int ltype, rtype, symtab_descriptor;/**/
	switch(lookahead) 
	{
		case BEGIN: match(BEGIN);stmtlist();match(END);
			break;
		case IF:
			match(IF);expr(BOOL);match(THEN);stmt();
			if(lookahead==ELSE){match(ELSE);stmt();}
			break;
		case WHILE:
			match(WHILE);expr(BOOL);match(DO);stmt();
			break;
		case REPEAT:
			match(REPEAT);stmtlist();match(UNTIL);expr(BOOL);
			break;
		case ID:
			/**/symtab_descriptor = systab_lookup(lexeme);/**/
			/**/if(symtab_decriptor){
				ltype = symtab[symtab_descriptor].vtype;
			}else{
				fprintf(stderr,
				"left-assignment variable \"%s\" not declared\n",
				lexeme);
			}/**/
			match(ID);match(ASGMN);/**/rtype = /**/expr(0);
			/* treat left-right type compatibility */
			break;
		default: ;
	}
}

void stmtlist()
{
	STMT_LIST:
	stmt();
	if(lookahead == ';'){
	match(';'); goto STMT_LIST;
	}
}
	
void imperative (void)
{
	match(BEGIN);
	stmtlist();
	match(END);
	match('.');
}


void
match(int expected)
{
    if (expected == lookahead) {
        lookahead = gettoken(src);
    } else {
        fprintf(stderr, "token mismatch\n");
        fprintf(stderr, "expected %c ", expected);
        fprintf(stderr, "whereas found %c\n", lookahead);
        exit(-2);
    }
}


int isoplus(int oplus)
{
	switch (oplus) {
		case '+':
			/*6*/printf("\tacc = acc + stack[sp]; sp--;\n")/*6*/;
			return '+';
		case '-':
			/*7*/printf("\tacc = acc - stack[sp]; sp--;\n")/*7*/;
			return '-';		
	}

	return 0;
}

enum{
	NUMERIC=1,
	INTONLY,
	LOGICAL,
	LITERAL
};
int typeclass(){}

int operclass(int oper)
{
	switch(oper){
		case '+':case '-':case '*':case'/': return NUMERIC;
		case DIV: case MOD: return INTONLY;
		case NOT: case OR: case AND: return BOOL;
	}	
	return 0;
}

int isotimes (int otimes)
{
	switch (otimes) {
		case '*':
			/*8*/printf("\tacc = acc * stack[sp]; sp--;\n")/*8*/;
			return '*';
		case '/':
			/*9*/printf("\tacc = acc / stack[sp]; sp--;\n")/*9*/;
			return '/';
		case DIV:
			return DIV;
		case MOD:
			return MOD;
		case AND:
			return AND
	}
	return 0;	
}
/*pascal*/

int isnagate(void)
{
	switch(lookahead){
		case'-':	
		case NOT:
			return lookahead;
	}
	return 0;
}

/* typecheck ok*/
int expr(int inherited_type)
{
	/**/int otilde, oprnd1, oprnd2;/**/

	/**/oprnd1=/**/E(0);
	if (isotilde(/**/otilde = /**/lookahead)){
		match(otilde);
		/**/oprnd2=/**/E(/**/oprnd1/**/);
		/** typecheck begin**/
		if(oprnd2 < 0) {
			return oprnd2;
		}
		/** typecheck end**/
		/**/return BOOL;/**/
	}
	/**/return oprnd1;/**/
}

int E(int inherited_type)
{
	/**/int R_type, sign = 0, oplus=0, otimes=0, acctype = 0;/**/
	/**/char name[MAXSTRLEN+1];/**/


	E_start:
		
		if (/**/sign = /**/isnegate()) 
		match(sign);

	T_start:
	
	F_start:
		/*4*if(oplus+otimes) accpush()4*/

 	switch (lookahead){
	case ID:
		
		/**/strcpy(name,lexeme);/**/

		match(ID);

		if (lookahead == ASGNM){
			/**/ int L_type;/*dica*/
			match(ASGNM);
			/**/R_type = /**/E(/**/inherited-type/**/);
			/** type-compability check regarding L-type and R-type  fazer **/
   		}else{
			/**/int vardescriptor = symtab_lookup(name);
			if(vardescriptor > 0) {
				R_type = symtab[vardescriptor].vtype;
			} else {
				fprintf(stderr, "error: undeclared variable \"%s\"\n", name);
			}
			/**/
		}
		break;
		//const

	case FLT:
		/**/ R_type = flt2arch(lexeme);/**/
		match(FLT);
		break;

	case DEC:
		/**/ R_type = uint2arch(lexeme);/**/
		match(DEC);
		break;
	defaut:
		match('(');
		/**/R_type = /**/E(0);
		match(')');

	}

	/**/
	if(acctype == 0){
		acctype = R_type;
	}else{
		if(typeclass(acctype) == typeclass(R_type)){
			acctype =max(acctype, R_type);
		}else{
			fprintf(stderr, "error: type mismatch\n");
			acctype = TYPEMISMATCH;
		}
	}/**/
	
F_end:
	if(/**/otimes = /**/isotimes(lookahead)){
		/**/
		if(typeclass(acctype) != operclass(otimes)){
		fprintf(stderr, "error: \n");
		acctype = TYPEMISMATCH;
		}	
		match(lookahead);
		goto F_start;
	}
T_end:
	/*11*if(sign){
		printf("\tacc = -acc;\n");
		sign = 0;*/
	}
	if(isoplus(lookahead)){
		match(lookahead);
		goto T_start;
	}
E_end:
}

