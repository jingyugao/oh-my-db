
#include "json_parser.h"

using namespace omd;

const char *testKV[] = {"\"k1\":null", "\"k2\":1", "\"k3\":1.2",
                        "\"k4\":[1,2,3]", "\"k5\":{}"};
const char *testJson = "";

struct jsonTest : public json {
    void test()
    {
        for (int i = 0; i < sizeof(testKV) / sizeof(const char *); i++) {
            json::kv *kv1 = json::get_kv(testKV[i], strlen(testKV[i]));
            printf("parser %s ret\tk:%s,v:%s\n", testKV[i], kv1->k, kv1->v);
        }
    }
};


int main()
{
}