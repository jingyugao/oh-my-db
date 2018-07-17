#include<iostream>
#include<string>
#include<vector>
#include<cctype>
#include<cstdint>
#include<cstring>

using namespace std;

namespace omd{
    class json{
        enum json_type{
            j_illegal=-1,
            j_null,
            j_int,
            j_float,
            j_string,
            j_array,
            j_ptr,
        }
        
        struct node{
            json_type jt;
            char key[8];
            union{
                int d;
                float f;
                string s;
                vector<node*> a;
                node * p;
            }
        }
        struct jobj{
            list<node*> ln;
        }
        node * create_node(){
            node*n=new node;
            memset(n,0,sizeof(node));
        }
        // "k_1":"val"
        
        struct kv{
            char k[8];
            char v[1024];
        }

        kv*create_kv(){
            kv*r=new kv;
            memset(r,0,sizeof(kv));
            return r;
        }
        kv* get_kv(const char* str,int len){
            const char*end=str;
            const char*p2;
            assert(*str=='\"');
            node* n0=create_node();
            kv *r=create_kv();
            
            while(1){
                end++;
                if(end=='\"'){
                    //key end;
                    assert(end-sttr<4);
                    memcpy(r->k,str+1,end-str-1);
                    continue;
                }
                if(end==':'){
                    p1=end+1;
                    continue;
                }

                if(end==','||end=='}'){
                    memcpy(r->v,p1,end-p1-1);
                    break;
                }
            }
            return r;
        }

        void parser(const char* ){
            char str[]="{\"k1\":1,\"k_2\":0.3,\"k_3\":\"string\",\"k_4\":{},\"k_5\":[1,2,3,4],\"k_6\":null}";

            const char*p=str;
            int  j_begin=0;
            int  j_end=0;
            while(1){
                char c=*p;
                p++;
                if(isspace(c))
                    continue;
                
                switch(c){
                    case '{':
                        j_begin++;
                        break;
                    case '}':
                        j_end++;
                        break;
                    case '\"':
                        
                }


            }


        }




    }



}
