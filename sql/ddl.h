
#include"sql_parse.h"
#include"relation.h"
#include<memory>


class CreateRelation{

private:

    void init(){
        relation=new Relation();
        assert(sql_tree);
        assert(sql_tree->node_kind==SQL_CREATE);
        SqlNode*rel_node=sql_tree->u.create_node.rel_node
        assert(rel_node->node_kind==SQL_RELATION);
        
        relation->name=rel_node->u.rel_node.rel_name;
        
        for(SqlNode*cur=sql_tree->u.create_node.attr_list;cur;cur=cur->u.list_node.left_list){
            relation->attrs.emplace_back(Attribute(cur->u.attr_node.val_type,cur->u.attr_node.len,string(cur->u.attr_node.col_name)));
        }
    }

    void check(){

    }
    
    SqlNode *sql_tree;
    Relation *relation;
}