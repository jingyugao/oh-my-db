#include<iostream>
#include<cctype>

using namespace std;

namespace omd{
    struct Commond{
        int argc;
        char *argc[];

    };
    
    struct Jnode{
        union{

        }
    }


    // str={"argc":3,"argv":["set","k1","v1"]}
    
    Commond * parser(const char * s){
        
        while(1){
            if(isspace(*s)){
                continue;
            }

            if(*s=='{'){
                //parser begin 
                continue;
            }
        }

    }

}
