
%{

#include"sql_node.h"
static SqlNode *parse_tree;

extern FILE * ferr;
%}

%union{
int ival;
float fval;
char *sval;
int subtok;
struct SqlNode* n;
}




%token <sval>   WORD 
%token <sval>   LITERAL  
%token <ival>   INT 
%token <fval>   FLOAT 

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



%type <n>   sql 
            ddl 
            dml
            create_statmen
            insert_statment
            insert_values
            query_statment
            select_statment
            cond_statment
            cmp_statment
            column_list
            sql_value
            table_list
            table
            column
            



%%


start:                  sql   
                    |   select_statment  {fprintf(ferr,"start\n");  parse_tree=$1;   print_node(ferr,$1); }         
                    ;

sql:                    ddl
                    |   dml {fprintf(ferr,"sql\n");   $$=$1;}
                    ;



ddl:                    create_statmen
                    ;

dml:                    insert_statment
                    |   query_statment      { fprintf(ferr,"dml\n");  $$=$1;}
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

query_statment:          sel_statment cond_statment 
                    |    select_statment        {fprintf(ferr,"query_statment\n");  $$=$1;}
                    ;
select_statment:
                        SELECT column_list FROM table_list {fprintf(ferr,"sel_statment\n");   $$=select_node($2,$4);}
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
                    |   column ',' column_list   {$$=list_node($3,$1);}
                    |   column              {fprintf(ferr,"col_list\n"); $$=list_node($1,NULL);}
                    ;

sql_value:
                        INT
                    |   FLOAT
                    |   LITERAL
                    ;

table_list:             table ',' table_list   {$$=list_node($3,$1);}
                    |   table              {fprintf(ferr,"table_list\n");    $$=list_node($1,NULL);}
                    ;

column:                 table '.' WORD     {fprintf(ferr,"rel.col:%s.%s\n",$1,$3);$$=col_node($1,$3);}
                    |   WORD               {fprintf(ferr,"column:%s\n",$1);$$=col_node($1,"null");} 
                    ;   

table:                  WORD        {
                                        fprintf(ferr,"table:%c%cxx,\n",*($1),*($1+1));
                                        $$=rel_node($1);
                                        }          
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

