/**@<parser.h>::**/

extern FILE    *src;
extern int     lookahead;

void ommand(void);
int expr(int);
void stmt(void);
void stmtlist(void);
int isnagate(void);
int E(int);
int isoplus(int oplus);
int isotimes(int otimes);
int isotilde(int otilde);
void match(int);
int operclass(int oper)
