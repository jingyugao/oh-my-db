#include "db.h"

#include <sys/stat.h>

namespace omd {

void db::db(const string &name){
    this->_name=name;
    this->_path=string(DATA_PATH)+name+"/";
    int mk_err = mkdir(_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    
}

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

