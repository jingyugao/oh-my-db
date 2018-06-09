#ifndef DB_H
#define DB_H
#include "b_plus_tree.h"
#include <stack>
#include <string>
#include <vector>
using namespace std;

enum dbType { Int = 0, String = 1 };
namespace omd {
struct dbObject {
    int _key;
    string _data;
};
class db {
public:
    typedef int key_type;
    typedef pair<key_t, string> value_type;
    const string &getName() const { return _name; }
    void insert(const key_t primary_key, const string data)
    {
        dbObject d;
        d._key=primary_key;
        d._data=data;
        insert(d);
    }
    void insert(const dbObject &obj);

    dbObject *find(const key_type primary_key);

    void delele(const key_type primary_key);

private:
    void store();
    bplustree<key_type, dbObject *> _bpt;
    vector<dbObject> _data;
    stack<int> _freeNode;
    string _name;
};
} // namespace omd

#endif