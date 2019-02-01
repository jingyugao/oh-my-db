
#ifndef EXEC_PLAN_H
#define EXEC_PLAN_H
#include <set>
#include "iteator.h"
namespace omd
{
struct uniqueOP : public Iteator
{

    bool open()
    {
        srcIter->open();
        for (;;)
        {
            auto v = srcIter->getNext();
            if (v.NotFound)
            {
                break;
            }
            if (S.find(v.raw) == S.end())
            {
                S.insert(v.raw);
                records.push_back(v);
            }
        }
    }
    Iteator *getIter()
    {
    }
    vector<dbObject> records;
    set<void *> S;
    Iteator *srcIter;
};

} // namespace omd

#endif