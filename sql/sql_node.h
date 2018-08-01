#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
typedef enum { V_INT, V_FLOAT, V_STRING } ValType;

typedef struct {
    char *rel_name;
    char *col_name;
    ValType v_type;
    int len;
    void *data;
} ColItem;

typedef enum {
    SQL_CREATE,
    SQL_SELECT,
    SQL_RELATION,
    SQL_COLUMN,
    SQL_LIST
} SqlKind;

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
            //SqlNode* cond_list;
        } select_node;

        struct {
            struct SqlNode *cur_node;
            struct SqlNode *left_list;
        } list_node;
    } u;
} SqlNode;

SqlNode *base_node(SqlKind sql_kind)
{
    //printf("new node\n");
    SqlNode *node = (SqlNode *) malloc(sizeof(SqlNode));
    node->node_kind = sql_kind;
    return node;
}

SqlNode *create_node(char *rel_name, SqlNode *col_list)
{
    SqlNode *node = base_node(SQL_CREATE);
    node->u.create_node.rel_name = rel_name;
    node->u.create_node.col_list = col_list;
    return node;
}

SqlKind *select_node(SqlNode *col_list, SqlNode *rel_list)
{
    SqlNode *node = base_node(SQL_SELECT);
    node->u.select_node.col_list = col_list;
    node->u.select_node.rel_list = rel_list;
    return node;
}

SqlNode *list_node(SqlNode *cur, SqlNode *list)
{
    SqlNode *new_list = base_node(SQL_LIST);
    new_list->u.list_node.left_list = list;
    new_list->u.list_node.cur_node = cur;
    return new_list;
}
SqlNode *col_node(char *col_name, char *rel_name)
{
    SqlNode *node = base_node(SQL_COLUMN);
    node->u.col_node.col_name = col_name;
    node->u.col_node.rel_name = rel_name;
    return node;
}

SqlNode *rel_node(char *rel_name)
{
    SqlNode *node = base_node(SQL_RELATION);
    node->u.rel_node.rel_name = rel_name;
    return node;
}

#define GET_CUR(list,cur)  do{ assert(list->node_kind == SQL_LIST); cur=list->u.list_node.cur_node; }while(0)

#define GO_NEXT(list)      do{ assert(list->node_kind == SQL_LIST); list=list->u.list_node.left_list; }while(0)

void print_node(FILE *f, SqlNode *root)
{

    SqlNode *p = root;
    if (f == NULL || root == NULL)
        return;
    int n=p->node_kind;
    fprintf(f, "kind:%d\n", n);
    switch (n) {
        //fprintf(f,"begin switch\n");
        // case SQL_CREATE:
        //     fprintf(f, "SQL_CREATE:rel_name:%s,", p->u.create_node.rel_name);
        //     fprintf(f, "col_list:[");
        //     for (SqlNode *q = p->u.create_node.col_list; q;
        //          q = q->u.list_node.left_list) {
        //         assert(q->node_kind == SQL_LIST);
        //         SqlNode *col = q->u.list_node.cur_node;
        //         assert(col->node_kind == SQL_COLUMN);
        //         fprintf(f, "%s.%s,", col->u.col_node.rel_name,col->u.col_node.col_name);
        //     }
        //     fprintf(f, "]\n");
        //     break;
        case SQL_SELECT:
            printf("\nSQL_SELECT:");
            printf("col_list:[");
            SqlNode*q;
            for(q=p->u.select_node.col_list;q!=NULL;q=q->u.list_node.left_list){
                assert(q->node_kind==SQL_LIST);
                SqlNode *cur=q->u.list_node.cur_node;
                assert(cur->node_kind==SQL_COLUMN);
                if(cur->u.col_node.rel_name==NULL){
                    cur->u.col_node.rel_name="";
                }
                fprintf(f,"%s,",cur->u.col_node.col_name);
            }
            fprintf(f,"],");
            fprintf(f,"rel_list:[");
            for(q=p->u.select_node.rel_list;q;q=q->u.list_node.left_list){
                assert(q->node_kind==SQL_LIST);
                SqlNode *cur=q->u.list_node.cur_node;
                assert(cur->node_kind==SQL_RELATION);
                fprintf(f,"%s,",cur->u.rel_node.rel_name);
            }
            fprintf(f,"]\n");
            break;
        default:
            fprintf(f,"err kind:%d",p->node_kind);

    }
}
