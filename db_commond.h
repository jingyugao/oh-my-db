
#include <string>
#include<vector>

namespace omd
{
 

struct cmd_ret{

}

struct attr_info{

}

struct db_cmd{
    cmd_ret open_db(const string  db_name)=0;
    cmd_ret close_db();
    
    cmd_ret create_table(const string rel_name,const vector<attr_info> attrs);
    cmd_ret drop_table(const string table_name);

    cmd_ret create_index(const string table_name,const string attr_name);
    cmd_ret drop_index(const string table_name,const string attr_name);

    cmd_ret load(const string rel_name,const string file_name);
    
    cmd_ret help();
    cmd_ret help(const string rel_name);

    cmd_ret print(const string rel_name);
    cmd_ret set(const string param_name,const string value);

}

} // omd


