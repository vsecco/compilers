/**@<gettoken.h>::**/

#define		MAXSTRLEN 1024
extern char	lexeme[MAXSTRLEN+1];

char	lexeme[MAXSTRLEN+1];
	
enum {
    ID = 1024,
    DEC,
    FLT,
    NEQ,
    GEQ,
    LEQ,
    ASGMN,

};

int             gettoken(FILE *);	
