/**@<keywords.h>::*/
int iskeyword(char const *identifier);
enum keyword {
	BEGIN = 2048,
	VAR,
	BYTE,		/*int8 - 1*/
	WORD,		/*int16 - 2*/
	INTEGER,	/*int32 - 3*/
	LONGINT,	/*int64 - 4*/
	REAL,		/*flt32 - 5*/
	DOUBLE,		/*flt64 - 6*/
	BOOLEAN,	/*bool  - 7*/
	CHAR,		/*chr - 8*/
	STRING,		/*str - 9*/
	IF,
	THEN,
	ELSE,
	WHILE,
	DO,
	REPEAT,
	UNTIL,
	NOT,
	DIV,
	MOD,
	AND,
	OR,
	END
};
