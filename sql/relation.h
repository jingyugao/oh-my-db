
#include<string>
#include<vector>
#include <algorithm>

#include"sql_node.h"
#include"variant"
using namespace std;

struct Attribute{
    SqlValType value_type;
    int len;
    string name;
}
typedef variant<int,float,string> vt;

struct Record{


    vector<vt> values;
    char * buf;
    vector<Attribute> attrs;
}

class buffer{
    buffer(int size=4096){

    };
    
    char *data;
}

template

class Relation{
public:
    Relation(){
        buf=new char[4096];
    }
    // first one is primary key
    void insert(vector<vt> &v){
        char * rd=createRecord();
    }

private:

    char *createRecord(){
        // if(cur+rd_size*2<=buf_end){
        //     return cur+=rd_size;
        // }
        return new char[rd_size];
    }
    insertRecord(char *rd){
        int key=*(int*)rd;
        std::vector<char*>::iterator pos=lower_bound(rds.begin(),rds.end());
        rds.insert(pos,rd);
    }

    vector<Attribute> attrs;
    int rd_size;
    vector<char *> rds;
    string  name;
    // char *buf_start;
    // char *buf_end;
    // char *cur;
    //char * rds;
}