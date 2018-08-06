#include <cassert>
#include <cstdio>
#include <list>
#include <stdlib.h>
#include <string>
#include <utility>

#include"sql_parse.h"

extern "C" {
void yyerror(const char *s);
int yylex(void);
int yyparse(void);
}


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
SqlNode *insert_node(SqlNode *rel_node, SqlNode *val_list, SqlNode *col_list);
SqlNode *cond_node(SqlNode *const x, SqlOp op, SqlNode *const y);
SqlNode *list_node(SqlNode *const cur, SqlNode *const list);
SqlNode *col_node(char *col_name, char *const rel_name);
SqlNode *rel_node(char *const rel_name);
SqlNode *attr_node(char *col_name, SqlValType value_type, int len = 0);
SqlNode *db_node(char *db_name, SqlOp op);
SqlNode *set_node(SqlNode *col_node, SqlNode *val_node);
SqlNode *update_node(SqlNode *rel_node, SqlNode *set_list, SqlNode *cond_list);
SqlNode *delete_node(SqlNode *rel_node,SqlNode *cond_list);
void print_node(FILE *f, SqlNode *root);