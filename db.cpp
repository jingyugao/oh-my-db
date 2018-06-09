#include "db.h"
namespace omd {
void db::insert(const dbObject &obj)
{
    int pos = -1;
    if (!_freeNode.empty()) {
        pos = _freeNode.top();
        _freeNode.pop();
        _data[pos] = obj;
        _bpt.insert(obj._key, &_data[pos]);
    } else {
        _data.push_back(obj);
        _bpt.insert(obj._key, &_data.back());
    }
}
dbObject *db::find(const key_type primary_key)
{
    auto it = _bpt.find(primary_key);
    if (it == _bpt.end())
        return nullptr;
    return it->second;
}

void db::delele(const key_type primary_key)
{
    size_t ret = _bpt.erase(primary_key);
    assert(ret == 1);
}
void db::store() {}
} // namespace omd
