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

#include <gtest/gtest.h>
#include <myrtti.h>

#include <sstream>
#include <string>

TEST(Basic, SingleParent) {

    with_rtti_root(struct, TestRoot)
    with_rtti_end();

    with_rtti(struct, Final, TestRoot)
    with_rtti_end();

    Final instance;
    TestRoot *p = &instance;

    EXPECT_STREQ(p->rtti->name, "Final");
    EXPECT_EQ(p->rtti->getId(), Final::class_id());
}

TEST(Basic, ManyParents) {

    with_rtti_root(struct, TestRoot)
    with_rtti_end();

    with_rtti_root(struct, TestRoot2)
    with_rtti_end();

    with_rtti_parents(struct, Final, (TestRoot, TestRoot2))
    with_rtti_end();

    Final instance;
    myrtti::Object *p = &instance;

    auto *h = myrtti::Hierarchy::instance();

    EXPECT_STREQ(h->getClassInfo(Final::class_id())->name, "Final");
    EXPECT_TRUE(myrtti::Hierarchy::instance()->isParent(Final::class_id(), TestRoot::class_id()));
    EXPECT_TRUE(myrtti::Hierarchy::instance()->isParent(Final::class_id(), TestRoot2::class_id()));
}

TEST(Basic, VirtualPrents) {

    //        Base
    //     /   |   \
    //    v    v    v
    //    A    B    C
    //     \   |   /| [virtual]
    //      \  |  / |
    //       v v v  |
    //         X   / [virtual]
    //         |  /
    //         v v
    //          Z

    struct Construct {
        static std::ostringstream& out() {
            static std::ostringstream v;
            return v;
        }
    };

    struct Destruct {
        static std::ostringstream& out() {
            static std::ostringstream v;
            return v;
        }
    };


    with_rtti_root(struct, Base)
    with_rtti_end();

    with_rtti(struct, A, Base)
        A() { Construct::out() << "A"; }
        ~A() override { Destruct::out() << "A"; }
    with_rtti_end();

    with_rtti(struct, B, Base)
        B() { Construct::out() << "B"; }
        ~B() override { Destruct::out() << "B"; }
    with_rtti_end();

    with_rtti(struct, C, Base)
        C() { Construct::out() << "C"; }
        ~C() override { Destruct::out() << "C"; }
    with_rtti_end();

    with_rtti_vparents_parents(struct, X, (C), (A, B))
        X() { Construct::out() << "X"; }
        ~X() override { Destruct::out() << "X"; }
    with_rtti_end();

    with_rtti_vparents_parents(struct, Z, (C), (X))
        Z() { Construct::out() << "Z"; }
        ~Z() override { Destruct::out() << "Z"; }
    with_rtti_end();

    auto *h = myrtti::Hierarchy::instance();

    // Initiate hierarchy creation by calling info for interesting class.
    Z::info();

    // TODO: h->isParent<Z, C>();
    EXPECT_TRUE(h->isParent(Z::class_id(), C::class_id()));
    EXPECT_TRUE(h->isParent(Z::class_id(), A::class_id()));
    EXPECT_TRUE(h->isParent(Z::class_id(), B::class_id()));
    EXPECT_TRUE(h->isParent(X::class_id(), C::class_id()));
    EXPECT_TRUE(h->isParent(X::class_id(), A::class_id()));
    EXPECT_TRUE(h->isParent(X::class_id(), B::class_id()));

    std::ostringstream windupWalk;
    std::ostringstream unwindWalk;

    // TODO: h->windup<Z>([...]{...});
    h->windup(Z::class_id(), [&](const myrtti::ClassInfo *cls) {
        if (cls != myrtti::Object::info() and cls != Base::info())
            windupWalk << cls->name;
        return true;
    });
    h->unwind(Z::class_id(), [&](const myrtti::ClassInfo *cls) {
        if (cls != myrtti::Object::info() and cls != Base::info())
            unwindWalk << cls->name;
        return true;
    });

    // Pick construction and destruction traces
    {
        Z instance;
    }

    // Construction and destruction checked with two pair:
    // first - we check that we know c++, haha
    // second - we check that windup/unwind walks works as expected
    EXPECT_STREQ(Construct::out().str().c_str(), "CABXZ");
    EXPECT_STREQ(windupWalk.str().c_str(), "CABXZ");

    EXPECT_STREQ(Destruct::out().str().c_str(), "ZXBAC");
    EXPECT_STREQ(unwindWalk.str().c_str(), "ZXBAC");
}
