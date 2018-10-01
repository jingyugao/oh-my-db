#if !defined(QUEYY_H)
#define QUEYY_H
#include "relation.h"

#include <vector>
using namespace std;

struct Field {
    string name;
    int index;
    string rel_name;
};

class CondStatment {
};

enum QueryType {

    SELECT,
    INSERT,
    UPDATE,
    DELETE,
    CREATE_TABLE,
    DROP_TABLE
};

class Utility {
    QueryType type;
    SqlNode *rel;
    vector<SqlNode *> attr_list;
}

struct TreeNode {
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;

    SqlNode *cond;
}

struct Query {

    QueryType type;

    SqlNode *utility;

    SqlNode *into_relation;
    vector<SqlNode *> rel_list;
    vector<SqlNode *> col_list;
    vector<SqlNode *> val_list;
    SqlNode *cond_list;
    vector<SqlNode *> join_list;
};

#define f stdout
Query *build(SqlNode *root)
{

    Query *qry = new Query();
    Utility *u;
    std::vector<SqlNode *> l;

    SqlNode *p = root;
    int n = p->node_kind;
    fprintf(f, "kind:%d\n", n);
    switch (n) {
        case SQL_CREATE:
            fprintf(f, "SQL_CREATE:rel_name:%s,",
                    p->u.create_node.rel_node->u.rel_node.rel_name);
            u = new Utility();
            qry->utility = u;
            qry->QueryType = CREATE_TABLE;
            u->QueryType = CREATE_TABLE;
            u->rel = p->u.create_node.rel_node;
            fprintf(f, "col_list:[");
            for (SqlNode *q = p->u.create_node.attr_list; q;
                 q = q->u.list_node.left_list) {
                assert(q->node_kind == SQL_LIST);
                SqlNode *attr = q->u.list_node.cur_node;
                assert(attr->node_kind == SQL_ATTR);
                attr_list.push_back(attr);
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
            qry->QueryType = SELECT;

            for (q = p->u.select_node.col_list; q != NULL;
                 q = q->u.list_node.left_list) {
                assert(q->node_kind == SQL_LIST);
                SqlNode *cur = q->u.list_node.cur_node;
                assert(cur->node_kind == SQL_COLUMN);
                qry->rel_list.push_back(cur);
                fprintf(f, "%s.%s,", cur->u.col_node.rel_name,
                        cur->u.col_node.col_name);
            }
            fprintf(f, "]\n");

            fprintf(f, "rel_list:[");
            for (q = p->u.select_node.rel_list; q;
                 q = q->u.list_node.left_list) {
                assert(q->node_kind == SQL_LIST);
                SqlNode *cur = q->u.list_node.cur_node;
                qry->rel_list.push_back(cur);
                assert(cur->node_kind == SQL_RELATION);
                fprintf(f, "%s,", cur->u.rel_node.rel_name);
            }
            fprintf(f, "]\n");

            fprintf(f, "cond_list:[");
            q = p->u.select_node.cond_list;
            qry->cond_list = q;
            l.push_back(q);
            PrintCondNode(l, max_depth(q));
            fprintf(f, "]\n");
            break;

        case SQL_INSERT:
            fprintf(f, "\nSQL_INSERT:\n");
            assert(p->node_kind == SQL_INSERT);
            qry->QueryType = INSERT;
            fprintf(f, "rel_name:%s,",
                    p->u.insert_node.rel_node->u.rel_node.rel_name);
            qry->rel = p->u.insert_node.rel_node;
            fprintf(f, "val_list:[");
            for (q = p->u.insert_node.val_list; q;
                 q = q->u.list_node.left_list) {
                assert(q->node_kind == SQL_LIST);
                SqlNode *cur = q->u.list_node.cur_node;
                q->val_list.push_back(cur);
                PrintValueNode(cur, f);
            }
            fprintf(f, "]");

            fprintf(f, "col_list:[");
            for (q = p->u.insert_node.col_list; q;
                 q = q->u.list_node.left_list) {
                assert(q->node_kind == SQL_LIST);
                SqlNode *cur = q->u.list_node.cur_node;

                assert(cur->node_kind == SQL_COLUMN);
                q->col_list.push_back(cur);

                fprintf(f, "%s.%s,", cur->u.col_node.rel_name,
                        cur->u.col_node.col_name);
            }
            fprintf(f, "\n]\n");
            break;
        default:
            fprintf(f, "unkonwn kind:%d", p->node_kind);
    }

#endif // QUEYY_H
