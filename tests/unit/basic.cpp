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
    const TestRoot *pConst = &instance;

    EXPECT_STREQ(p->rtti->name, "Final");
    EXPECT_EQ(p->rtti->getId(), myrtti::class_id<Final>());
}

TEST(Basic, DynCast) {

    with_rtti_root(struct, TestRoot)
    with_rtti_end();

    with_rtti_root(struct, TestRoot2)
    with_rtti_end();

    with_rtti(struct, Final, TestRoot)
    with_rtti_end();

    Final instance;
    TestRoot2 instance2;
    TestRoot *p = &instance;
    const TestRoot *pConst = &instance;

    auto *pp = myrtti::dyn_cast<Final*>(&instance);
    auto *pp2 = myrtti::dyn_cast<Final*>(&instance2);

    auto &r = p->cast<Final>();
    auto *pp3 = p->cast<Final*>();

    const auto &rConst = p->cast<Final&>();
    const auto *pp3Const = p->cast<Final*>();

    EXPECT_NE(pp, nullptr);
    EXPECT_EQ(pp2, nullptr);
    EXPECT_NE(pp3, nullptr);
    EXPECT_NE(pp3Const, nullptr);
}

TEST(Basic, TryStatic) {

    with_rtti_root(struct, TestRoot)
    with_rtti_end();

    with_rtti(struct, Final, TestRoot)
    with_rtti_end();

    with_rtti(struct, Final2, TestRoot)
    with_rtti_end();

    Final instance;
    Final2 instance2;

    TestRoot* p = &instance;
    TestRoot* p2 = &instance2;

    auto *pp = myrtti::try_static_cast<Final*>(p);
    auto *pp2 = myrtti::try_static_cast<TestRoot*>(&instance);
    auto *pp3 = myrtti::try_static_cast<Final*>(p2);

    EXPECT_NE(pp, nullptr);
    EXPECT_NE(pp2, nullptr);
    EXPECT_STREQ(pp->rtti->name, "Final");
    EXPECT_STREQ(pp2->rtti->name, "Final");

    EXPECT_EQ(pp3, nullptr);
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

    EXPECT_STREQ(h->getClassInfo(myrtti::class_id<Final>())->name, "Final");
    EXPECT_TRUE(myrtti::Hierarchy::instance()->isParent(myrtti::class_id<Final>(), myrtti::class_id<TestRoot>()));
    EXPECT_TRUE(myrtti::Hierarchy::instance()->isParent(myrtti::class_id<Final>(), myrtti::class_id<TestRoot2>()));
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
    EXPECT_TRUE(h->isParent(myrtti::class_id<Z>(), myrtti::class_id<C>()));
    EXPECT_TRUE(h->isParent(myrtti::class_id<Z>(), myrtti::class_id<A>()));
    EXPECT_TRUE(h->isParent(myrtti::class_id<Z>(), myrtti::class_id<B>()));
    EXPECT_TRUE(h->isParent(myrtti::class_id<X>(), myrtti::class_id<C>()));
    EXPECT_TRUE(h->isParent(myrtti::class_id<X>(), myrtti::class_id<A>()));
    EXPECT_TRUE(h->isParent(myrtti::class_id<X>(), myrtti::class_id<B>()));

    std::ostringstream windupWalk;
    std::ostringstream unwindWalk;

    // TODO: h->windup<Z>([...]{...});
    h->windup(myrtti::class_id<Z>(), [&](const myrtti::ClassInfo *cls) {
        if (cls != myrtti::Object::info() and cls != Base::info())
            windupWalk << cls->name;
        return true;
    });
    h->unwind(myrtti::class_id<Z>(), [&](const myrtti::ClassInfo *cls) {
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
