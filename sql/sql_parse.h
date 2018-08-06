




enum SqlValType {
    SQL_NULL,    //"null"
    SQL_INT,     //"int"
    SQL_FLOAT,   //"float"
    SQL_CHAR,    //"char"
    SQL_LITERAL, //not used now
    SQL_VARCHAR, //"varchar"
    SQL_ARRAY    //"array"
};



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
    SQL_DB,
    SQL_SET,
    SQL_UPDATE,
    SQL_DELETE
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
static char *OpStr[] = {"eq", "gt", "lt", "le", "ge", "ne", "ad", "or", "nt"};


struct SqlNode {
    SqlKind node_kind;
    union {
        struct {
            struct SqlNode *rel_node;
            struct SqlNode *attr_list;
        } create_node;

        struct {
            struct SqlNode *rel_node;
        } drop_node;

        struct {
            SqlOp db_op;
            char *db_name;
        } db_node;

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
            SqlNode *col_list; //option
        } insert_node;

        struct {
            struct SqlNode *X; //val_node or cond_node
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
            SqlNode *val_node;
            SqlNode *col_node;
        } set_node;

        struct {
            SqlNode *rel_node;
            SqlNode *set_list;
            SqlNode *cond_list;
        } update_node;

        struct {
            SqlNode *rel_node;
            SqlNode *cond_list;
        } delete_node;

        struct {
            struct SqlNode *cur_node;
            struct SqlNode *left_list;
        } list_node;
    } u;
};


SqlNode* sql_parser(const char* sql_str);