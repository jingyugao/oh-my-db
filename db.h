#ifndef DB_H
#define DB_H

#include "b_tree.h"
#include "cfg_def.h"
#include <stack>
#include <string>
#include <vector>
#include "iteator.h"
using namespace std;

namespace omd
{

typedef string key_type;

enum dbValType
{
  Int = 1,
  String = 2
};

struct Value
{
  int kind;
  int len;
  char *data;
};
class table;

struct dbObject
{
  map<string, Value> data;
  void *raw;
};
struct ColAttr
{
  string name;
  int kind;
  int offset;
  int len;
};
struct sheame
{
  vector<ColAttr> attrs;
};
// class table
// {
//   public:
//     table(string name) {}
//     void fileScan() {}

//   private:
//     string _name;
//     string pryKey;
//     BTree<string, dbObject *> _data;

//     db *_db;
// };


class index
{
public:

  Iteator *getIter()
  {
    Iteator *i=new idxIter(this);

    return i;
  }

private:
  friend class idxIter;
  table *_table;
  BTree<key_type, dbObject> _bpt;
};

class table
{
public:
  table(const string &name);

  typedef pair<key_t, string> value_type;
  
  void insert(const key_t primary_key, const void *data)
  {
    dbObject d;
    insert(d);
  }
  void insert(dbObject obj);

  dbObject *find(const key_type primary_key);

  void delele(const key_type primary_key);

private:
  void store();
  string _pryKey;
  BTree<key_type, dbObject> _bpt;
  stack<int> _freeNode;
  string _name;
  string _path;
};




} // namespace omd

#endif