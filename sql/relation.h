
#include<string>
#include<vector>
#include"sql_node.h"
#include"variant"
using namespace std;

struct Attribute{
    SqlValType value_type;
    string name;
}
typedef variant<int,float,string> vt;

struct Record{
    vector<vt> values;
}

class Relation{
public:

private:
    vector<Attribute> attrs;
    string  name;
    vector<Record> rds;
}