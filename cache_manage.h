#ifndef CACHE_MANAGE_H
#define CACHE_MANAGE_H
#include <iostream>
#include <queue>
#include <string>
#include <map>
using namespace std;
namespace omd
{

class CachBase
{
  public:
    virtual void *Get(string k) = 0;
    virtual void Del(string k);
    virtual void SetRealGet(void *(*)(string));
};

struct LRUNode
{
    LRUNode *prev;
    LRUNode *next;
    void *data;
};

class LRU : public CachBase
{
  public:
    LRU(int cap = 64);
    void *Get(string k)
    {
        auto v = data.find(k);
        if (v != data.end())
        {
            return v->second;
        }

        int size = this->data.size();
        LRUNode* one;
        if (size == cap)
        {
            one=removeFront();
        }else{
            one=new(LRUNode);
        }
        moveToTail(one);
        one->data=realGet(k);
    }
    void Del(string){
        void(0);
    }
    void SetRealGet(void *(*realGet)(string))
    {
        this->realGet = realGet;
    }

  private:
    LRUNode *removeFront()
    {
        assert(head == tail);
        
        LRUNode *one = head->next;
        head->next = one->next;
        one->next->prev = one->prev;
        return one;
    }

    void moveToTail(LRUNode *one)
    {
        assert(one != head);
        assert(one != tail);

        one->prev = tail->prev;
        one->next = tail;
        tail->prev->next = one;
        tail->prev = one;
    }
    int cap;
    LRUNode *head;
    LRUNode *tail;
    void *(*realGet)(string);
    map<string, void *> data;
};
} // namespace omd

#endif