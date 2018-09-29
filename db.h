#ifndef DB_H
#define DB_H

#include "b_plus_tree.h"
#include "cfg_def.h"
#include <stack>
#include <string>
#include <vector>
using namespace std;

enum dbType { Int = 0, String = 1 };
namespace omd {
struct column {
    int primary_key;
};



class table {
public:
    table(string name) {}

private:
    column *insert(column*){ }
    column *get_raw(int n) { return (column *) (_data + n * _col_size); }
    string _name;

    char *_data;
    int _col_size;
    db *_db;
}

class index {
public:
private:
    table *_table;
    bplustree<key_type, dbObject *> _bpt;

}

class db {
public:
    db(const string &name);

    typedef int key_type;
    typedef pair<key_t, string> value_type;

    void insert(const key_t primary_key, const string data)
    {
        dbObject d;
        d._key = primary_key;
        d._data = data;
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
    string _path;
};

} // namespace omd

#endif