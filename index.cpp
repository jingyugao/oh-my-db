#include "index.h"

namespace omd
{

Iteator *index::getIter()
{
    Iteator *i = new idxIter(this);
    return i;
}
} // namespace omd