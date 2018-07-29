
%{

struct sql_val{
    int v_type;
    void * val;
}

struct sql_node{
    int sql_type;//create 1,select2,insert 3,
}


%}


%union{
int ival;
float fval;
char *sval;
int subtok;
}

%token WORD CHAR
%token LITERAL  
%token INT FLOAT 

%token 
    NONE
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
create_statmen:CREATE table 

insert_statment:   
                        INSERT INTO table VALUES '(' insert_values ')'

insert_values:   
                        sql_value
                    |   insert_values,sql_value
                    ;

query_statment:
                        select_statment WHERE cond_statment
                    ;
select_statment:
                        SELECT column_list FROM table 
                        ;
cond_statment:
                        cond_statment AND cond_statment
                    |   cond_statment OR cond_statment
                    |   NOT cond_statment
                    |   '(' cond_statment ')'
                    |   cmp_statment
            
cmp_statment:
                        column op column
                    ;   

column_list:
                        column
                    |   column_list ',' column
                    |   (char*)"*"
                    ;

sql_value:
                        INT
                    |   FLOAT
                    |   LITERAL


table:                  WORD
                    ;
column:
                        WORD
                    |   WORD '.' WORD
                    ;   




op: 
    EQ
  | LT 
  | GT 
  | LE 
  | GE 
  | NE
  ;
        


%%

