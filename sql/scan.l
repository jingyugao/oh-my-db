%{
#include<string.h>
//#include"sql.h"
#include"y.tab.h"

#define MAX_LEN 255

int yyerror(char*);

typedef struct{
    const char*token_str;
    int token_type;
}token_struct;

token_struct token_map[]={
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

char *make_string(const char*src,int len){
    char *ret=(char*)malloc(len);
    //ret[0] is " 
    memcpy(ret,src+1,len-2);
    ret[len-1]='\0';
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
    
    yylval.sval=s;
    for(int i=0;i<sizeof(token_map)/sizeof(token_struct);i++){
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
{s_num}         {yylval.ival=atoi(yytext);return INT;}
{s_num}\.{num}  {yylval.fval=atof(yytext);return FLOAT;}
\"(\\.|[^\\"])*\" {yylval.sval=make_string(yytext,yyleng);return LITERAL;}
\"(\\.|[^\\"])*\n   {printf("newline in literal string is illegal!\n");}
{letter}({letter}|{digit}|_)*    { return  get_id(yylval.sval=yytext) ;}
"<"         {return LT;}
"<="        {return LE;}
">"         {return GT;}
">="        {return GE;}
"="         {return EQ;}
"!="        {return NE;}

%%
main(int argc,char **argv){
    return yyparse();
}





