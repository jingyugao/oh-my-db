#include"cache_manage.h"

namespace omd{

LRU::LRU(int size){
    _q.resize(size);
}

}