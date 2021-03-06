/*
 * Copyright (C) 2017-2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "cl_api_tests.h"

using namespace NEO;

typedef api_tests clUnloadCompilerTests;

namespace ULT {

TEST_F(clUnloadCompilerTests, notImplemented) {
    auto retVal = clUnloadCompiler();
    EXPECT_EQ(CL_OUT_OF_HOST_MEMORY, retVal);
}
} // namespace ULT
