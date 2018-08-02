#include"sql_node.h"


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

SqlNode *select_node(SqlNode *col_list, SqlNode *rel_list, SqlNode *cond_list)
{
    SqlNode *node = base_node(SQL_SELECT);
    node->u.select_node.col_list = col_list;
    node->u.select_node.rel_list = rel_list;
    node->u.select_node.cond_list = cond_list;
    return node;
}

SqlNode *value_node(void * x, SqlValType t)
{
    SqlNode *node = base_node(SQL_VALUE);
    node->u.val_node.v_type = t;
    switch (t) {
        case SQL_INT:
            node->u.val_node.ival = *(int *) x;
            break;
        case SQL_FLOAT:
            node->u.val_node.fval = *(float *) x;
            break;
        case SQL_LITERAL:
            node->u.val_node.sval = (char *) x;
        default:
            printf("err SqlValType:%d,val:%s", t, x);
    }
    return node;
}

SqlNode *cond_node( SqlNode * const x, SqlOp op, SqlNode *const y)
{
    SqlNode *node = base_node(SQL_COND);

    node->u.cond_node.X = x;
    node->u.cond_node.Y = y;
    node->u.cond_node.op = op;
    // if (x->node_kind==SQL_COLUMN&&y->node_kind==SQL_COLUMN){

    // }

    // if (x->node_kind==SQL_COLUMN&&y->node_kind==SQL_VALUE){

    // }

    // if (x->node_kind==SQL_VALUE&&y->node_kind==SQL_COLUMN){

    // }

    // if (x->node_kind==SQL_VALUE&&y->node_kind==SQL_VALUE){

    // }

    return node;
}

SqlNode *list_node( SqlNode *const cur, SqlNode *const list)
{
    SqlNode *new_list = base_node(SQL_LIST);
    new_list->u.list_node.left_list = list;
    new_list->u.list_node.cur_node = cur;
    return new_list;
}
SqlNode *col_node( char *col_name,  char *const rel_name)
{
    SqlNode *node = base_node(SQL_COLUMN);
    node->u.col_node.col_name = col_name;
    node->u.col_node.rel_name = rel_name;
    return node;
}

SqlNode *rel_node(char * const rel_name)
{
    SqlNode *node = base_node(SQL_RELATION);
    node->u.rel_node.rel_name = rel_name;
    return node;
}



void print_node(FILE *f, SqlNode *root)
{
    SqlNode *p = root;
    if (f == NULL || root == NULL)
        return;
    int n = p->node_kind;
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
            SqlNode *q;
            for (q = p->u.select_node.col_list; q != NULL;
                 q = q->u.list_node.left_list) {
                assert(q->node_kind == SQL_LIST);
                SqlNode *cur = q->u.list_node.cur_node;
                assert(cur->node_kind == SQL_COLUMN);
                fprintf(f, "%s,", cur->u.col_node.col_name);
            }
            fprintf(f, "],");

            fprintf(f, "rel_list:[");
            for (q = p->u.select_node.rel_list; q;
                 q = q->u.list_node.left_list) {
                assert(q->node_kind == SQL_LIST);
                SqlNode *cur = q->u.list_node.cur_node;
                assert(cur->node_kind == SQL_RELATION);
                fprintf(f, "%s,", cur->u.rel_node.rel_name);
            }
            fprintf(f, "]\n");

            fprintf(f, "cond_list:[");
            q = p->u.select_node.cond_list;
            if (q) {
                SqlNode *x = q->u.cond_node.X;
                SqlOp op = q->u.cond_node.op;
                SqlNode *y = q->u.cond_node.Y;

                if (x->node_kind == SQL_COLUMN) {
                    fprintf(f,"%s.%s ", x->u.col_node.rel_name,
                            x->u.col_node.col_name);
                }

                switch(op){
                    case SQL_EQ:
                        fprintf(f,"=");
                        break;
                }
                if (y->node_kind == SQL_COLUMN) {
                    fprintf(f,"%s.%s ", y->u.col_node.rel_name,
                            y->u.col_node.col_name);
                }

                fprintf(f, "]\n");
            }

            break;
        default:
            fprintf(f, "err kind:%d", p->node_kind);
    }
}