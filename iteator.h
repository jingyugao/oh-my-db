#ifndef ITEATOR_H
#define ITEATOR_H
#include "db_object.h"
#include "b_tree.h"

namespace omd
{
class index;
class Iteator
{
  virtual bool open() = 0;
  virtual dbObject getNext();
  virtual bool close();
};

class idxIter : public Iteator
{
public:
  idxIter(index *i = nullptr);
  bool open();
  bool hasNext();
  dbObject getOne();
  bool close();

private:
  BTree<key_type, dbObject>::loc cur;
  index *idx;
};
} // namespace omd

#endif