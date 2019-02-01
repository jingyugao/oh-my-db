#ifndef DB_OBJECT_H
#define DB_OBJECT_H
#include <map>
using namespace std;
namespace omd
{

enum dbValType
{
    Int = 1,
    String = 2
};
typedef string key_type;


struct Value
{
    int kind;
    int len;
    char *data;
};
struct dbObject
{   
    map<string, Value> data;
    void *raw;
    bool NotFound;
};

} // namespace omd
#endif
