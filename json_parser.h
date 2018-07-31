#include <cctype>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;


bool is_in(char c,const string s){
    for(int i=0;i<s.size();i++){
        if(s[i]==c)
            return true;
    }
    return false;
}
vector<string> split(const string str,const char *separator ){
    vector<string> ret;
    
    int j=0;
    for(int i=0;i<str.size();i++){
        if()

    }
}

namespace omd {
class json {
public:

    enum json_type {
        j_illegal = -1,
        j_null,
        j_int,
        j_float,
        j_string,
        j_array,
        j_ptr,
    };

    struct node {
        json_type jt;
        char key[8];
        //union{
        int d;
        float f;
        string s;
        vector<node *> a;
        node *p;
        //}
    };
    struct jobj {
        list<node *> ln;
    };
    static node *create_node()
    {
        node *n = new node;
        memset(n, 0, sizeof(node));
        return n;
    }
    // "k_1":"val"

    struct kv {
        char k[8];
        char v[1024];
    };

    static kv *create_kv()
    {
        kv *r = new kv;
        memset(r, 0, sizeof(kv));
        return r;
    }
    struct V {
        union {
            int d;
            float f;
            string s;
            vector<node *> a;
            node *p;
        };
    };
    static create_V()
    {
        V *v = new V();
        memset(v, 0, sizeof(V));
        return v;
    }
    static V *parser_val(const char *str)
    {
        V *v = new V();
        const char *p = str;
        int t;

        char c = *p;

        if (p[0] == 'n' && p[1] == 'u' && p[2] == 'l' && p[3] == 'l') {
            t = j_null;
        } else if (isdigit(c)) {
            bool has_dot=false;
            

        } else if (c == '\"') {

        } else if (c == '[') {

        } else if (c == '{') {
        } else {
            t = j_illegal;
        }
    }
    static kv *get_kv(const char *str, int len)
    {
        assert(*str == '\"');
        kv *r = create_kv();
        int i = 0;
        while (i < len && str[i] != ':')
            i++;
        if (i == len) {
            //error
            assert(0);
        }
        memcpy(r->k, str + 1, i - 2);
        memcpy(r->v, str + i + 1, len - i - 1);
        return r;
    }

    void parser(const char *)
    {
        char str[] = "{\"k1\":1,\"k_2\":0.3,\"k_3\":\"string\",\"k_4\":{},\"k_"
                     "5\":[1,2,3,4],\"k_6\":null}";

        const char *p = str;
        int j_begin = 0;
        int j_end = 0;
        while (1) {
            char c = *p;
            p++;
            if (isspace(c))
                continue;

            switch (c) {
                case '{':
                    j_begin++;
                    break;
                case '}':
                    j_end++;
                    break;
            }
        }
    }
};

} // namespace omd
