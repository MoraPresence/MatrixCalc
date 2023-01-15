// Copyright 2022 mora

#include <gtest/gtest.h>

#include "Tests_Add_Sub.h"
#include "Tests_Creation.h"
#include "Tests_Determinant.h"
#include "Tests_Elem_by_Elem.h"
#include "Tests_Indexes.h"
#include "Tests_Multiply.h"
#include "Tests_Slices.h"
#include "Tests_Transp_Invert.h"

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
