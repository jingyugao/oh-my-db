#ifndef CACHE_MANAGE_H
#define CACHE_MANAGE_H
#include <iostream>
#include <queue>
using namespace std;
namespace omd {

class CachBase {
public:
    virtual void acccess(int k) = 0;
};

class LRU : public CachBase {
public:
    LRU(int size = 64);
    void acccess(int k);

private:
    queue<int> _q;
};
} // namespace omd

#endif