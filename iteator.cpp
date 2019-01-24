#include "iteator.h"
#include "db_object.h"
#include "index.h"

namespace omd
{
idxIter::idxIter(index *i)
{
    idx = i;
}
bool idxIter::open()
{
    cur = idx->_bpt.begin();
    return true;
}
bool idxIter::hasNext()
{
    return !(cur == idx->_bpt.right());
}
dbObject idxIter::getOne()
{
    dbObject v = cur.getVal();
    cur = cur.next();
    return v;
}
bool idxIter::close()
{
    return true;
}
} // namespace omd