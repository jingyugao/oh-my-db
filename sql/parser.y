%union{
int ival;
float fval;
char *sval;
int subtok;
}

%token WORD 
%token LITERAL  
%token INT FLOAT 

%token 
    NONE
    CHAR
    CREATE
    DROP
    TABLE
    INDEX
    HELP
    VALUES
    INSERT
    DELET
    UPDATE
    AND
    XOR
    OR
    EQ
    NE
    LT
    LE
    GT
    GE



%token SELECT FROM WHERE

%%

select_statment:
               SELECT column FROM table
               ;
table:      WORD
     ;
column:     WORD
      ;



%%

