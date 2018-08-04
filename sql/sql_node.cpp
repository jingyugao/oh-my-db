#include "sql_node.h"

SqlNode *base_node(SqlKind sql_kind)
{
    //printf("new node\n");
    SqlNode *node = (SqlNode *) malloc(sizeof(SqlNode));
    node->node_kind = sql_kind;
    return node;
}

SqlNode *create_node(SqlNode *rel_node, SqlNode *col_list)
{
    SqlNode *node = base_node(SQL_CREATE);
    node->u.create_node.rel_node = rel_node;
    node->u.create_node.col_list = col_list;
    return node;
}

SqlNode *drop_node(SqlNode *rel_node)
{
    SqlNode *node = base_node(SQL_DROP);
    node->u.drop_node.rel_node = rel_node;
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

SqlNode *value_node(void *x, SqlValType t)
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
        case SQL_VARCHAR:
            node->u.val_node.sval = (char *) x;
            break;
        default:
            printf("err SqlValType:%d,val:%c", t, x);
    }
    return node;
}

SqlNode *insert_node(SqlNode *rel_node, SqlNode *val_list, SqlNode *col_list)
{
    SqlNode *node = base_node(SQL_INSERT);
    node->u.insert_node.rel_node = rel_node;
    node->u.insert_node.val_list = val_list;
    node->u.insert_node.col_list = col_list;
    return node;
}

SqlNode *cond_node(SqlNode *const x, SqlOp op, SqlNode *const y)
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

SqlNode *list_node(SqlNode *const cur, SqlNode *const list)
{
    SqlNode *new_list = base_node(SQL_LIST);
    new_list->u.list_node.left_list = list;
    new_list->u.list_node.cur_node = cur;
    return new_list;
}
SqlNode *col_node(char *col_name, char *const rel_name)
{
    SqlNode *node = base_node(SQL_COLUMN);
    node->u.col_node.col_name = col_name;
    node->u.col_node.rel_name = rel_name;
    return node;
}

SqlNode *rel_node(char *const rel_name)
{
    SqlNode *node = base_node(SQL_RELATION);
    node->u.rel_node.rel_name = rel_name;
    return node;
}

SqlNode *attr_node(char *col_name, SqlValType value_type, int len)
{
    SqlNode *node = base_node(SQL_ATTR);
    node->u.attr_node.col_name = col_name;
    node->u.attr_node.val_type = value_type;
    switch (value_type) {
        case SQL_INT:
            len = sizeof(int);
            break;
        case SQL_FLOAT:
            len = sizeof(float);
        case SQL_VARCHAR:
            break;
        default:
            printf("err value_type");
            break;
    }
    node->u.attr_node.len = len;
    return node;
}

SqlNode *db_node(char *db_name, SqlOp op)
{
    SqlNode *node = base_node(SQL_DB);
    node->u.db_node.db_name = db_name;
    node->u.db_node.db_op = op;
    return node;
}

static const char *get_value_type_name(SqlValType t)
{
    switch (t) {
        case SQL_NULL:
            return "null";
        case SQL_INT:
            return "int";
        case SQL_FLOAT:
            return "float";
        case SQL_CHAR:
            return "char";
        case SQL_VARCHAR:
            return "varchar";
        case SQL_ARRAY:
            return "array";
        default:
            return "unknow";
    }
}

#define PrintValueNode(node, f)                                                \
    do {                                                                       \
        assert(node->node_kind == SQL_VALUE);                                  \
        switch (node->u.val_node.v_type) {                                     \
            case SQL_INT:                                                      \
                fprintf(f, "int(%d),", node->u.val_node.ival);                 \
                break;                                                         \
            case SQL_FLOAT:                                                    \
                fprintf(f, "float(%f),", node->u.val_node.fval);               \
                break;                                                         \
            case SQL_VARCHAR:                                                  \
                fprintf(f, "varchar(%s),", node->u.val_node.sval);             \
                break;                                                         \
            default:                                                           \
                fprintf(f, "unknow,");                                         \
        }                                                                      \
    } while (0);

void print_node(FILE *f, SqlNode *root)
{
    SqlNode *p = root;
    if (f == NULL || root == NULL)
        return;
    int n = p->node_kind;
    fprintf(f, "kind:%d\n", n);
    switch (n) {
        case SQL_CREATE:
            fprintf(f, "SQL_CREATE:rel_name:%s,",
                    p->u.create_node.rel_node->u.rel_node.rel_name);
            fprintf(f, "col_list:[");
            for (SqlNode *q = p->u.create_node.col_list; q;
                 q = q->u.list_node.left_list) {
                assert(q->node_kind == SQL_LIST);
                SqlNode *attr = q->u.list_node.cur_node;
                assert(attr->node_kind == SQL_ATTR);
                //if (attr->u.attr_node.val_type == SQL_VARCHAR) {
                fprintf(f, "%s.%s(%d),", attr->u.attr_node.col_name,
                        get_value_type_name(attr->u.attr_node.val_type),
                        attr->u.attr_node.len);
                // } else {
                //     fprintf(f, "%s.%s,", attr->u.attr_node.col_name,
                //             get_value_type_name(attr->u.attr_node.val_type));
                // }
            }
            fprintf(f, "]\n");
            break;
        case SQL_SELECT:
            fprintf(f, "\nSQL_SELECT:\n");
            fprintf(f, "col_list:[");
            SqlNode *q;
            for (q = p->u.select_node.col_list; q != NULL;
                 q = q->u.list_node.left_list) {
                assert(q->node_kind == SQL_LIST);
                SqlNode *cur = q->u.list_node.cur_node;
                assert(cur->node_kind == SQL_COLUMN);
                fprintf(f, "%s.%s,", cur->u.col_node.rel_name,
                        cur->u.col_node.col_name);
            }
            fprintf(f, "]\n");

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
                    fprintf(f, "%s.%s ", x->u.col_node.rel_name,
                            x->u.col_node.col_name);
                }

                if (x->node_kind == SQL_VALUE) {
                    fprintf(f, "%s(%s) ", x->u.val_node.ival,
                            x->u.col_node.col_name);
                }

                switch (op) {
                    case SQL_EQ:
                        fprintf(f, "=");
                        break;
                    case SQL_GT:
                        fprintf(f, ">");
                        break;
                    case SQL_LT:
                        fprintf(f, "<");
                        break;
                    case SQL_GE:
                        fprintf(f, ">=");
                        break;
                    case SQL_LE:
                        fprintf(f, "<=");
                        break;
                    case SQL_AND:
                        fprintf(f, "and");
                        break;
                    case SQL_OR:
                        fprintf(f, "or");
                        break;
                    case SQL_NOT:
                        fprintf(f, "not");
                        break;
                    default:
                        fprintf(f, "unknow");
                }
                if (y->node_kind == SQL_COLUMN) {
                    fprintf(f, "%s.%s ", y->u.col_node.rel_name,
                            y->u.col_node.col_name);
                }
            }
            fprintf(f, "]\n");
            break;

        case SQL_INSERT:
            fprintf(f, "\nSQL_INSERT:\n");
            assert(p->node_kind == SQL_INSERT);
            fprintf(f, "rel_name:%s,",
                    p->u.insert_node.rel_node->u.rel_node.rel_name);

            fprintf(f, "val_list:[");
            for (q = p->u.insert_node.val_list; q;
                 q = q->u.list_node.left_list) {
                assert(q->node_kind == SQL_LIST);
                SqlNode *cur = q->u.list_node.cur_node;
                PrintValueNode(cur,f);
            }
            fprintf(f, "]");

            fprintf(f, "col_list:[");
            for (q = p->u.insert_node.col_list; q;
                 q = q->u.list_node.left_list) {
                assert(q->node_kind == SQL_LIST);
                SqlNode *cur = q->u.list_node.cur_node;
                assert(cur->node_kind == SQL_COLUMN);
                fprintf(f, "%s.%s,", cur->u.col_node.rel_name,
                        cur->u.col_node.col_name);
            }
            fprintf(f, "]\n");

        default:
            fprintf(f, "konwn kind:%d", p->node_kind);
    }
}