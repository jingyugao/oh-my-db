%{
#include<string.h>
#include<stdio.h>
#include"sql_node.h"
#include"y.tab.h"

#define MAX_LEN 255
FILE * ferr;
extern SqlNode *parse_tree;
char *make_string(const char*src,int len);
char *get_literal(const char *src,int len);
int get_id(char* s);
int lower(char *dst, char *src, int max);
typedef struct{
    const char*token_str;
    int token_type;
}TokenItem;

TokenItem token_map[]={
    {"create",CREATE},
    {"drop",DROP},
    {"table",TABLE},
    {"index",INDEX},
    {"and",AND},
    {"values",VALUES},
    {"select",SELECT},
    {"from",FROM},
    {"where",WHERE},
    {"insert",INSERT},
    {"delete",DELET},
    {"update",UPDATE}

}; 

char *get_literal(const char *src,int len){
    char *dst=make_string(src+1,len-2);
    dst[len-1]='\0';
    return dst;
}
char *make_string(const char*src,int len){
    char *ret=(char*)malloc(len+1);

    memcpy(ret,src,len+1);
    return ret;
}

int get_id(char* s){
 
    static char str[MAX_LEN];
    int len;

    if((len = lower(str, s, MAX_LEN)) == MAX_LEN)
    {
        fprintf(stderr,"TOKEN length is over than MAX_LEN:%d",MAX_LEN);
        return NONE;
    }
    
    yylval.sval=make_string(s,len);
    for(int i=0;i<sizeof(token_map)/sizeof(TokenItem);i++){
        if (strcmp(str,token_map[i].token_str)==0)
            return yylval.ival=token_map[i].token_type;
    }

    return WORD;
}

int lower(char *dst, char *src, int max)
{
   int len;

   for(len = 0; len < max && src[len] != '\0'; ++len){
      dst[len] = src[len];
      if(src[len] >= 'A' && src[len] <= 'Z')
         dst[len] += 'a' - 'A';
   }
   dst[len] = '\0';

   return len;
}


%}
letter      [A-Za-z]
digit       [0-9]
num         {digit}+
s_num       [+\-]?{num}

%x COMMENT

%%
"/*"            {BEGIN(COMMENT);}
<COMMENT>[^*]   {/*ingore the '*' */}
<COMMENT>"*/"   {BEGIN(INITIAL);}
[ \n\t]         {/* ignore whilespace */}
{s_num}         {yylval.ival=atoi(yytext);fprintf(ferr,"INT:%d",yylval.ival);  return INT;}
{s_num}\.{num}  {yylval.fval=atof(yytext);return FLOAT;}
\"(\\.|[^\\"])*\" {yylval.sval=get_literal(yytext,yyleng);fprintf(ferr,"LITERAL:%s",yylval.sval);  return LITERAL;}
\"(\\.|[^\\"])*\n   {printf("newline in literal string is illegal!\n");}
{letter}+    { int id=get_id(yytext);fprintf(ferr,"id:%d,val:%s\n",id,yytext);   return id;}
"<"         {return LT;}
"<="        {return LE;}
">"         {return GT;}
">="        {return GE;}
"="         {return EQ;}
"!="        {return NE;}

%%

SqlNode* sql_parser(const char* sql_str){
    // ferr=fopen("err.log","w");
    // if(ferr==NULL){
    //     printf("cant open err.log\n");
    //     return 0;
    // }
    ferr=stdout;
    setbuf(ferr,NULL);

    fprintf(ferr,"begin log\n");
    yy_scan_string(sql_str);
    yyparse();
    return parse_tree;
}






