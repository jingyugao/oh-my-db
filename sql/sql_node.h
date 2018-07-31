


typedef {
    char *rel_name;
    char *col_name;
}RelCol;


typedef enum {
    V_INT,
    V_FLOAT,
    V_STRING
}ValType;

typedef{
    RelCol name;
    ValType v_type;
    int     len;
    void *data;
}ColVal;


