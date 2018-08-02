#include <cassert>
#include <cstdio>
#include <stdlib.h>
extern "C"//为了能够在C++程序里面调用C函数，必须把每一个需要使用的C函数，其声明都包括在extern "C"{}块里面，这样C++链接时才能成功链接它们。extern "C"用来在C++环境下设置C链接类型。
{	//lex.l中也有类似的这段extern "C"，可以把它们合并成一段，放到共同的头文件main.h中
	void yyerror(const char *s);
	int yylex(void);//该函数是在lex.yy.c里定义的，yyparse()里要调用该函数，为了能编译和链接，必须用extern加以声明
    int yyparse(void);
}


typedef enum { SQL_INT, SQL_FLOAT, SQL_LITERAL } SqlValType;

typedef struct {
    char *rel_name;
    char *col_name;
    SqlValType v_type;
    int len;
    void *data;
} ColItem;

typedef struct {

} ValItem;

typedef enum {
    SQL_CREATE,
    SQL_SELECT,
    SQL_RELATION,
    SQL_COLUMN,
    SQL_LIST,
    SQL_VALUE,
    SQL_COND
} SqlKind;

 enum SqlOp{
    SQL_EQ,
    SQL_GT,
    SQL_LT,
    SQL_LE,
    SQL_GE,
    SQL_NE,
    SQL_AND,
    SQL_OR,
    SQL_NOT
} ;


struct BaseNode{

};

struct Relation{
    
};

struct CreateNode:public BaseNode{

};
struct SelectNode:public BaseNode{

};
struct CondNode:public BaseNode{

};
struct ListNode:public BaseNode{

};
struct ColNode:public BaseNode{

};


typedef struct SqlNode {
    SqlKind node_kind;
    union {
        struct {
            char *rel_name;
            struct SqlNode *col_list;
        } create_node;

        struct {
            char *col_name;
            char *rel_name;
        } col_node;

        struct {
            char *rel_name;
        } rel_node;

        struct {
            struct SqlNode *col_list;
            struct SqlNode *rel_list;
            struct SqlNode *cond_list; //is not list
        } select_node;

        struct {
            struct SqlNode *X;
            struct SqlNode *Y;
            SqlOp op;
        } cond_node;

        struct {
            int ival;
            float fval;
            char *sval;
            int len;
            SqlValType v_type;
        } val_node;

        struct {
            struct SqlNode *cur_node;
            struct SqlNode *left_list;
        } list_node;
    } u;
} SqlNode;

#define GET_CUR(list, cur)                                                     \
    do {                                                                       \
        assert(list->node_kind == SQL_LIST);                                   \
        cur = list->u.list_node.cur_node;                                      \
    } while (0)

#define GO_NEXT(list)                                                          \
    do {                                                                       \
        assert(list->node_kind == SQL_LIST);                                   \
        list = list->u.list_node.left_list;                                    \
    } while (0)

SqlNode *base_node(SqlKind sql_kind);
SqlNode *create_node(char *rel_name, SqlNode *col_list);
SqlNode *select_node(SqlNode *col_list, SqlNode *rel_list, SqlNode *cond_list);
SqlNode *value_node(void * x, SqlValType t);
SqlNode *cond_node( SqlNode * const x, SqlOp op, SqlNode *const y);
SqlNode *list_node( SqlNode *const cur, SqlNode *const list);
SqlNode *col_node( char *col_name,  char *const rel_name);
SqlNode *rel_node(char * const rel_name);
void print_node(FILE *f, SqlNode *root);