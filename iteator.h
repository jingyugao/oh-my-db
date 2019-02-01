#ifndef ITEATOR_H
#define ITEATOR_H
#include "db_object.h"
#include "b_tree.h"

namespace omd
{
class index;
struct Iteator
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
  dbObject getNext();
  bool close();

private:
  BTree<key_type, void*>::loc cur;
  index *idx;
};
} // namespace omd

#endif