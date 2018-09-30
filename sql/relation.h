
#include <algorithm>
#include <string>
#include <vector>

#include <utility>
#include <variant>

#include "sql_node.h"

using namespace std;
class Index;

struct Attribute {
    SqlValType value_type;
    int len;
    string name;
};
typedef variant<int, float, string> vt;

struct Record {

    const vt &get_val(const string name){
        int i=0;
        while(i< attrs.size()&&attrs[i].name!=name){
            i++;
        }
        if (i>=attrs.size()){
            return vt();
        }else{
            return values[i];
        }
    }
    vector<vt> values;
    char *buf;

};

class buffer {
    buffer(int size = 4096){

    };

    char *data;
};

class Relation {
public:
    Relation() { buf = new char[4096]; }


    // first one is primary key
    void insert(const vector<vt> &vals)
    {

        if (!checkRecord(vals)) {
            return;
        }

        char *rd = createRecord();
        char *p = rd;
        int x = 0;
        for (int i = 0; i < v.size(); i++) {
            SqlValType t = attrs[i].value_type;
            switch (t) {
                case SQL_INT:
                    *(int *) p = vals[i].get<int>();
                    break;
                case SQL_FLOAT:
                    *(float *) p = vals[i].get<float>();
                    break;
                case SQL_VARCHAR:
                    string str = get<string>(vals[i]);
                    assert(str.size() < attrs[i].len);
                    memcpy(p, str.c_str(), str.size());
                    break;
                default:
                    assert(0);
            }
            p += attrs[i].len;
            assert(p==rd+rd_size);
        }
    }

    void remove(int primary_key){


    }

    Record get_record(int primary_key){
        Record r;
        r.attrs=attrs;
        //r.buf=
        return r;
    }

    vt get_val(const char * rd,const string &col_name){
        for(auto it=attrs.begin();it!=attrs.end();++it){
            if(it->name==col_name){
                switch(it->value_type){
                    
                }
            }
        }

    }



    void create(const string &name, const vector<Attribute> &attrs)
    {
        this->name = name;
        this->attrs = attrs;
        rd_size = 0;
        for (auto it = attrs.begin(); it != attrs.end(); ++it) {
            rd_size += it->len;
        }
        // assert(sql_tree);
        // assert(sql_tree->node_kind==SQL_CREATE);
        // SqlNode*rel_node=sql_tree->u.create_node.rel_node
        // assert(rel_node->node_kind==SQL_RELATION);

        // name=rel_node->u.rel_node.rel_name;
        // rd_size=0;
        // for(SqlNode*cur=sql_tree->u.create_node.attr_list;cur;cur=cur->u.list_node.left_list){
        //     attrs.emplace_back(Attribute(cur->u.attr_node.val_type,cur->u.attr_node.len,string(cur->u.attr_node.col_name)));
        //     rd_size+=cur->u.attr_node.len;
        // }
    }



    void drop(){

    }

    bool checkRecord(const vector<vt> &v) { return 1; }

    char *createRecord()
    {
        // if(cur+rd_size*2<=buf_end){
        //     return cur+=rd_size;
        // }
        return new char[rd_size];
    }
    insertRecord(char *rd)
    {
        int key = *(int *) rd;
        std::vector<char *>::iterator pos = lower_bound(rds.begin(), rds.end());
        rds.insert(pos, rd);
    }
    vector<Index> indexs;
    vector<Attribute> attrs;
    int rd_size;
    vector<char *> rds;
    string name;

    SqlNode *sql_tree;
    // char *buf_start;
    // char *buf_end;
    // char *cur;
    //char * rds;
};

class Index{




}