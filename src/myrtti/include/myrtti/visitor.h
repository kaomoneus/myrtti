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

#include "myrtti/runtime.h"
#include "myrtti/hierarchy.h"

#include <iostream>
#include <functional>
#include <unordered_map>
#include <utility>

#if 0
#define TRACE std::cout
#else
#include "utils/nullout.h"
#define TRACE myrtti::nullout_t::instance()
#endif

namespace myrtti
{
    template<bool istrue, class TrueT, class FalseT>
    struct __conditional {
        using type = TrueT;
    };

    template<class TrueT, class FalseT>
    struct __conditional<false, TrueT, FalseT> {
        using type = FalseT;
    };

    /// @brief Implements a visitor pattern which visits const references.
    ///
    /// Usage example:
    ///
    /// VisitorConst visitor(
    ///     [](const Exception& e) {
    ///         cout << "TEST EXCEPTION: Exception, msg: " << e.message << "\n";
    ///         return true;
    ///     },
    ///     [](const ExceptionErrorOne& e) {
    ///         cout << "TEST EXCEPTION: ExceptionOne.\n";
    ///         return true;
    ///     },
    ///     [](const ExceptionErrorTwo& e) {
    ///         cout << "TEST EXCEPTION: ExceptionTwo.\n";
    ///         return true;
    ///     }
    /// );
    /// visitor.visit(ExceptionErrorTwo());
    ///
    template<bool immutable = true>
    struct Visitor {
        using object_ref = std::conditional_t<immutable, const Object&, Object&>;

        template<class ...Lambda>
        explicit Visitor(Lambda&& ...L) {
            init(std::function(L)...);
        }

        template<class ...Cls>
        void init(
            std::function<bool(Cls&)>&& ...visitors
        ) {
            (
                [&] {
                    static_assert(
                        !immutable || std::is_const_v<Cls>,
                        "Please use type with 'const' qualifier while using"
                        " immutable visitor"
                    );

                    static_assert(
                        immutable || !std::is_const_v<Cls>,
                        "Please use type without 'const' qualifier while using"
                        " mutable visitor"
                    );
                    TRACE << "VISITOR: Registered handler for "
                              << Cls::info() << "\n";
                    visitorsMap.emplace(
                        Cls::class_id(),
                        [=] (object_ref b) {
                            Cls& bb = b.template cast<Cls>();
                            return visitors(bb);
                        }
                    );
                } (), ...
            );
        }

    bool visit(object_ref b) {
        TRACE << "VISITOR: Unwinding visit for class "
                  << b.rtti->name << "\n";

        bool neverVisited = Hierarchy::instance()->unwind(
            b.rtti->getId(),
            [&](const ClassInfo *cls) {
                TRACE << std::hex
                << "VISITOR:   Visiting class " << cls << "\n";
                auto found = visitorsMap.find(cls->getId());

                if (found != end(visitorsMap)) {
                    TRACE << "VISITOR:     found handler...\n";

                    bool visitHandled = found->second(b);
                    // If visit was successfull, stop going through
                    // hierarchy and exit.
                    return !visitHandled;
                }
                TRACE << "VISITOR:     handler not found.\n";

                return true;
            }
        );
        return !neverVisited;
    }

    private:
        std::unordered_map<
            class_id_t,
            std::function<bool(object_ref b)>
        > visitorsMap;
    };

    /// @brief Implements visiting for "static" case. Given particular
    /// class it goes through hierarchy and looks for available handler
    /// for this class or for one of its parents.
    ///
    /// Usage example:
    ///
    /// VisitorStatic staticVisitor({
    ///     {
    ///         Exception::info(), [] {
    ///             std::cout << "STATIC: Exception\n";
    ///             return true;
    ///         }
    ///     },
    ///     {
    ///         ExceptionErrorOne::info(), [] {
    ///             std::cout << "STATIC: ExceptionOne\n";
    ///             return true;
    ///         }
    ///     },
    ///     {
    ///         ExceptionErrorTwo::info(), [] {
    ///             std::cout << "STATIC: ExceptionTwo\n";
    ///             return true;
    ///         }
    ///     }
    /// });
    ///
    /// staticVisitor.visit(ExceptionErrorOne::info());
    ///
    struct VisitorStatic {

        explicit VisitorStatic(
            const std::unordered_map<
                class_id_t, std::function<bool()>
            >& handlers
        ) : visitorsMap(handlers) {}

        template<class ClassT>
        bool visit() {
            TRACE << "STATIC VISITOR: Unwinding visit for class " << ClassT::info() << "\n";

            bool neverVisited = Hierarchy::instance()->unwind(
                ClassT::class_id(),
                [&](const ClassInfo *cls) {
                    TRACE << std::hex
                    << "STATIC VISITOR:   Visiting class " << cls << "\n";
                    auto found = visitorsMap.find(cls->getId());

                    if (found != end(visitorsMap)) {
                        TRACE << "STATIC VISITOR:     found handler...\n";

                        bool visitHandled = found->second();
                        // If visit was successfull, stop going through
                        // hierarchy and exit.
                        return !visitHandled;
                    }
                    TRACE << "STATIC VISITOR:     handler not found.\n";

                    return true;
                }
            );
            return !neverVisited;
        }

    private:
        std::unordered_map<class_id_t, std::function<bool()>> visitorsMap;
    };
} // namespace myrtti
