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

dbObject idxIter::getNext()
{
    dbObject v;
    if(cur==idx->_bpt.end()){
       v.NotFound=true;
       return v;
    }
    v.raw = cur.getVal();
    cur = cur.next();
    return v;
}
bool idxIter::close()
{
    return true;
}
} // namespace omd