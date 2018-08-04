#include <cassert>
#include <cstdio>
#include <list>
#include <stdlib.h>
#include <string>
#include <utility>
extern "C" {
void yyerror(const char *s);
int yylex(void);
int yyparse(void);
}

enum SqlValType {
    SQL_NULL,   //"null"
    SQL_INT,    //"int"
    SQL_FLOAT,  //"float"
    SQL_CHAR,   //"char"
    SQL_LITERAL,//not used now
    SQL_VARCHAR,//"varchar"
    SQL_ARRAY   //"array"
};





struct {
    char *rel_name;
    char *col_name;
    SqlValType v_type;
    int len;
    void *data;
} ColItem;

enum SqlKind {
    SQL_CREATE,
    SQL_SELECT,
    SQL_INSERT,
    SQL_RELATION,
    SQL_DROP,
    SQL_COLUMN,
    SQL_ATTR,
    SQL_LIST,
    SQL_VALUE,
    SQL_CONST,
    SQL_COND,
    SQL_DB
};

enum SqlOp {
    SQL_EQ,
    SQL_GT,
    SQL_LT,
    SQL_LE,
    SQL_GE,
    SQL_NE,
    SQL_AND,
    SQL_OR,
    SQL_NOT,
    DB_CREATE,
    DB_DROP,
    DB_CLEAR,

};

// struct BaseNode {
//     SqlKind kind;
// };

// struct RelationNode:public BaseNode {
//     char *name;
// };

// struct ConstNode :public BaseNode{
//     SqlValType value_type;
//     int len;
//     void *data;
// };

// struct ColumnDef{
//     char *col_name;
//     SqlValType value_type;
//     char *rel_name;
//     //int len;
// };

// typedef std::pair<char*,char*> RelCol;

// template<SqlKind k>
// struct StatmentNode:public BaseNode{
// };

// template<>
// struct StatmentNode<SQL_CREATE>{
//     char *rel_name;
//     std::list<ColumnDef *> col_list;
// };

// template<>
// struct StatmentNode<SQL_SELECT>{
//     std::list<char *> from_clause;
//     std::list<RelCol> select_target;
//     BaseNode *where_clause;
// };
// template<>
// struct StatmentNode<SQL_COND>{
//     std::list<BaseNode*> items;     //op or const or column
// };

// struct CreateNode : public BaseNode {
//     char *rel_name;
//     std::list<ColumnDef *> col_list;
// };

// struct SelectNode : public BaseNode {
//     std::list<char *> from_clause;
//     std::list<RelCol> select_target;
//     BaseNode *where_clause;
// };

// struct CondNode:public BaseNode{
//     std::list<BaseNode*> items;     //op or const or column
// };

//  constexpr   BaseNode * createNode(const SqlKind kind){
//         BaseNode *node;
//         return node;


struct SqlNode {
    SqlKind node_kind;
    union {
        struct {
            struct SqlNode *rel_node;
            struct SqlNode *col_list;
        } create_node;

        struct {
            struct SqlNode *rel_node;
        } drop_node;

        struct {
            SqlOp    db_op;
            char * db_name;
        }db_node;
       
        struct {
            char *col_name;
            char *rel_name;
        } col_node;

        struct {
            char *col_name;
            SqlValType val_type;
            int len;
        } attr_node;

        struct {
            char *rel_name;
        } rel_node;

        struct {
            struct SqlNode *col_list;
            struct SqlNode *rel_list;
            struct SqlNode *cond_list; //is not list
        } select_node;

        struct {
            SqlNode *rel_node;
            SqlNode *val_list;
            SqlNode *col_list;//option
        } insert_node;

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
};

SqlNode *sql_parser(const char *sql_str);

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
SqlNode *create_node(SqlNode *rel_node, SqlNode *attr_list);
SqlNode *drop_node(SqlNode *rel_node);
SqlNode *select_node(SqlNode *col_list, SqlNode *rel_list, SqlNode *cond_list);
SqlNode *value_node(void *x, SqlValType t);
SqlNode *insert_node(SqlNode*rel_node,SqlNode *val_list,SqlNode *col_list);
SqlNode *cond_node(SqlNode *const x, SqlOp op, SqlNode *const y);
SqlNode *list_node(SqlNode *const cur, SqlNode *const list);
SqlNode *col_node(char *col_name, char *const rel_name);
SqlNode *rel_node(char *const rel_name);
SqlNode *attr_node(char *col_name, SqlValType value_type, int len = 0);
SqlNode *db_node(char *db_name,SqlOp op);
void print_node(FILE *f, SqlNode *root);