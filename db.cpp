#include "db.h"

#include <sys/stat.h>

namespace omd
{

table::table(const string &name)
{
    this->_name = name;
    this->_path = string(DATA_PATH) + name + "/";
    int mk_err = mkdir(_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

void table::insert(dbObject obj)
{
    auto val = obj.data.find(_pryKey);
    string k;
    if (val == obj.data.end())
    {
        k = "autoIncrement";
    }
    k = string(val->second.data);
    _bpt.insert(k, obj);
}
dbObject *table::find(const key_type primary_key)
{
}

void table::delele(const key_type primary_key)
{
    // size_t ret = _bpt.erase(primary_key);
    // assert(ret == 1);
}
void table::store() {}
} // namespace omd
