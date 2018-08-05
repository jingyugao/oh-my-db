#include "sql_node.h"

class Pretreat {
public:
private:
    SqlNode *sql_tree;
}

class SelectStatmen {
public:
    int check_relation();
    int check_column();  
    int check_type(); 
private:
    SqlNode *sql_tree;
    
}