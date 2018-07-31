
%{

struct sql_val{
    int v_type;
    void * val;
};

struct sql_node{
    int sql_type;//create 1,select2,insert 3,
};


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
    INTO
    AND
    XOR
    OR
    NOT
    EQ
    NE
    LT
    LE
    GT
    GE



%token SELECT FROM WHERE

%%


sql:                    ddl
                    |   dml
                    ;


ddl:                    create_statmen
                    ;

dml:                    insert_statment
                    |   query_statment
                    ;

create_statmen:         CREATE table
                    ;

insert_statment:   
                        INSERT INTO table VALUES '(' insert_values ')'
                    ;

insert_values:   
                        insert_values ','  sql_value
                    |   sql_value
                    ;

query_statment:
                        select_statment WHERE cond_statment
                    ;
select_statment:
                        SELECT column_list FROM table_list
                        ;
cond_statment:
                        cond_statment AND cmp_statment
                    |   cond_statment OR cmp_statment
                    |   NOT cond_statment
                    |   '(' cond_statment ')'
                    |   cmp_statment
                    ;
            
cmp_statment:
                        column op column
                    ;   

column_list:
                        column
                    |   column_list ',' column
                    |   '*'
                    ;

sql_value:
                        INT
                    |   FLOAT
                    |   LITERAL
                    ;

table_list:             table_list ',' table
                    |   table
                    ;

column:
                        table '.' WORD
                    ;   

table:                  WORD
                    ;


op: 
                        EQ
                    |   LT 
                    |   GT 
                    |   LE 
                    |   GE 
                    |   NE
                    ;
        


%%

