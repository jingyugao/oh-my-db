#pragma once

#include "third_party/bpt.h"

namespace omd {
template <typename _Key, typename _Data>
using bplustree = stx::btree<_Key, _Data>;
} // namespace omd