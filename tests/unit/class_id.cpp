// Copyright 2023 Stepan Dyatkovskiy at Kaspersky Lab.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <array>
#include <gtest/gtest.h>
#include <crc/crc.hpp>
#include <myrtti.h>
#include <sstream>

TEST(ClassId, Crc) {

    crc::CRC64 x, y, z;
    auto xx = x(1);
    auto yy = y(1, "qwe");

    std::array<int, 3> zzz{1,2,3};
    auto zz = z.array(begin(zzz), end(zzz));

    EXPECT_NE(xx, yy);
    EXPECT_NE(xx, zz);
    EXPECT_NE(yy, zz);
}


TEST(ClassId, ClassId) {

    myrtti::class_id_t x{"qwe"};
    myrtti::class_id_t y0{"qweqwe"};
    myrtti::class_id_t y1{"qwe", "qwe"};
    myrtti::class_id_t z{"qwe", "qwe", 1};

    std::ostringstream xx, yy0, yy1, zz;

    xx << x;
    yy0 << y0;
    yy1 << y1;
    zz << z;

    EXPECT_STREQ(xx.str().c_str(), "29aa-a28d-da3d-cec1");
    EXPECT_STREQ(yy0.str().c_str(), "54a1-2f75-8c0e-9996");
    EXPECT_STREQ(yy1.str().c_str(), "54a1-2f75-8c0e-9996");
    EXPECT_STREQ(zz.str().c_str(), "955b-6b44-099d-85b0");

    EXPECT_NE(x, y0);
    EXPECT_EQ(y0, y1);
    EXPECT_NE(x, z);
    EXPECT_NE(y0, z);

    EXPECT_NE(x.value, y0.value);
    EXPECT_EQ(y0.value, y1.value);
    EXPECT_NE(x.value, z.value);
    EXPECT_NE(y0.value, z.value);
}
