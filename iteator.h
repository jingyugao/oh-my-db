#ifndef ITEATOR_H
#define ITEATOR_H

#include "db.h"

namespace omd
{

class Iteator
{
  virtual bool open() = 0;
  virtual dbObject getNext();
  virtual bool close();
};

class idxIter : public Iteator
{
public:
  idxIter(index *i = nullptr)
  {
    idx = i;
  }
  bool open()
  {
    cur = idx->_bpt.begin();
    return true;
  }
  bool hasNext()
  {
    return !(cur == idx->_bpt.right());
  }
  dbObject getOne()
  {
    dbObject v = cur.getVal();
    cur = cur.next();
    return v;
  }
  bool close()
  {
    return true;
  }

private:
  BTree<key_type, dbObject>::loc cur;
  index *idx;
};
} // namespace omd

#endif