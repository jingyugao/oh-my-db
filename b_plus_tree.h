#ifndef B_PLUS_TREE_H
#define B_PLUS_TREE_H

#include "third_party/bpt.h"
namespace omd {
template <typename _Key,
          typename _Data,
          typename _Traits = stx::btree_default_map_traits<_Key, _Data> >
using bplustree =
    stx::btree<_Key, _Data, std::pair<_Key, _Data>, std::less<_Key>, _Traits>;
} // namespace omd
#endif