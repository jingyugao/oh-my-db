#if !defined(QUEYY_H)
#define QUEYY_H
#include"relation.h"
using namespace std;


struct Field{
    string name;
    int index;
    string rel_name;
};


class CondStatment{

};




class Query{
public:
enum class CmdType { 
    SELECT,
    INSERT,
    UPDATE,
    DELETE,
};
    Query(){
        
    };
private:

    SqlNode * into_relation;
    SqlNode * utilityStmt;
    SqlNode * rel_list; 
    SqlNode * col_list;

    
};


#endif // QUEYY_H
