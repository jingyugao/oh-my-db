
#ifndef INDEX_H
#define INDEX_H

#include "iteator.h"
#include"db.h"
using namespace std;
namespace omd
{

class index
{
public:
  Iteator *getIter();

private:
  friend class idxIter;
  table *_table;
  BTree<key_type, dbObject> _bpt;
};

} // namespace omd

#endif