/*
 * Copyright (C) 2017-2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "runtime/utilities/heap_allocator.h"

namespace NEO {

bool operator<(const HeapChunk &hc1, const HeapChunk &hc2) {
    return hc1.ptr < hc2.ptr;
}
} // namespace NEO
