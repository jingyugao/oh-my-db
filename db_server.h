#ifndef DB_SERVER_H
#define DB_SERVER_H 
#include "db.h"
#include <vector>
namespace omd {
struct op {
};
class dbServer {
public:
    vector<op> parse(const string &str) { return vector<op>(); }


public:
    db *create_db(const string &name){
        
    }
}
} // namespace omd
#endif