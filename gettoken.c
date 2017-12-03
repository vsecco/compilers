/**@<gettoken.c>::**/

#include <ctype.h>
#include <stdio.h>
#include <gettoken.h>
#include <keywords.h>
#define		MAXSTRLEN 1024
extern char	lexeme[MAXSTRLEN+1];

char	lexeme[MAXSTRLEN+1];

void
skipspaces(FILE * tape)
{
    int             head;
    while (isspace(head = getc(tape)));
    ungetc(head, tape);
}

int
isID(FILE * tape)
{
    int             head;
    int i = 0;

    int var = head = getc(tape);

    printf("VAR === %d", var);

    if (isalpha(var)) {

            printf("IS ALPHA === ");
	lexeme[i] = head; //FAZER EM TODOS
	i++;
        while (isalnum(head = getc(tape))){
		
		if(i < MAXSTRLEN) {//FAZER EM TODOS
		lexeme[i] = head;		
		i++;
		}
	}
        ungetc(head, tape);
	lexeme[i] = 0;
        return iskeyword(lexeme) || ID;
    }
    ungetc(head, tape);
    return 0;
}

int
isDEC(FILE * tape)
{
    int             head;

    if (isdigit(head = getc(tape))) {
	lexeme[i] = head;
        if (head == '0') {
            return DEC;
        }
        while (isdigit(head = getc(tape))){
		lexeme[i] = head;
	}
        ungetc(head, tape);
        return DEC;
    }
    ungetc(head, tape);
    return 0;
}

int
isEQ(FILE * tape)
{
    int             head;
    if ((head = getc(tape)) == '=') {
        if ((head = getc(tape)) == '=') {
            return EQ;
        }
        ungetc(head, tape);
        ungetc('=', tape);
        return 0;
    }
    ungetc(head, tape);
    return 0;
}

int
isNEQ(FILE * tape)
{
    int             head;
    if ((head = getc(tape)) == '!') {
        if ((head = getc(tape)) == '=') {
            return NEQ;
        }
        ungetc(head, tape);
        ungetc('!', tape);
        return 0;
    }
    ungetc(head, tape);
    return 0;
}

int
isGEQ(FILE * tape)
{
    int             head;
    if ((head = getc(tape)) == '>') {
        if ((head = getc(tape)) == '=') {
            return GEQ;
        }
        ungetc(head, tape);
        ungetc('>', tape);
        return 0;
    }
    ungetc(head, tape);
    return 0;
}

int
isLEQ(FILE * tape)
{
    int             head;
    if ((head = getc(tape)) == '<') {
        if ((head = getc(tape)) == '=') {
            return LEQ;
        }
        ungetc(head, tape);
        ungetc('<', tape);
        return 0;
    }
    ungetc(head, tape);
    return 0;
}



int gettoken(FILE * tape)
{
    int             token;
    skipspaces(tape);
   if ( (token = isID(tape))  ||
        (token = isDEC(tape)) 
	(token = isFLT(tape))||
        (token = isEQ(tape))  ||
        (token = isNEQ(tape)) ||
        (token = isGEQ(tape)) || 
	(token = isASGMN(tape))) return token;

    lexeme[0] = getc(tape);
    lexeme[1] = 0; 
    return lexeme[0];
}

int isSCI(FILE *tape){
  int head, sgn=0;
  int exp = (head = getc(tape));
  if(toupper(exp)=='E'){
    if((head = getc(tape))=='+' || head == '-'){
      sgn = head;
      if(!isdigit(head = getc(tape))){
	ungetc(head, tape);
	ungetc(sgn, tape);
	ungetc(exp, tape);
	return 0;
      } 
    }
    else
    {
      if(!isdigit(head))
	{
	  ungetc(head, tape);
	  ungetc(exp, tape);
	  return 0;
	}
    }
      while(isdigit(head = getc(tape)));
      return SCI;
  }
    ungetc(head, tape);
    return 0;
}

int isDECFP(FILE *tape){
    int head, token = 0;
    if(token == isDEC(tape)) {

     }
}

int isPLUS(FILE *tape)
{
	int head = getc(tape);

	switch (head) {
		case '+':
		case '-':
		return 3000;
	}

	ungetc(head, tape);

	return 0;
}
