#include "myrtti/runtime.h"
#include "myrtti/hierarchy.h"

#include <iostream>
#include <functional>
#include <unordered_map>
#include <utility>

namespace myrtti
{
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
    struct VisitorConst {

        template<class ...Lambda>
        explicit VisitorConst(Lambda&& ...L) {
            init(std::function(L)...);
        }

        template<class ...Cls>
        void init(std::function<bool(const Cls&)>&& ...visitors) {
            (
                [&] {
                    std::cout << std::hex
                    << "VISITOR: Registered handler for "
                    << Cls::info() << " " << Cls::info()->name << "\n";
                    visitorsMap.emplace(
                        Cls::info(),
                        [=] (const Object& b) {
                            const Cls& bb = *b.cast<Cls>();
                            return visitors(bb);
                        }
                    );
                } (), ...
            );
        }

    bool visit(const Object& b, bool notFoundResult = true) {
        std::cout << "VISITOR: Unwinding visit for class " << b.rtti->name << "\n";

        bool neverVisited = Hierarchy::instance()->destruct(
            b.rtti,
            [&] (const ClassInfo* cls) {
                std::cout << std::hex
                << "VISITOR:   Visiting class " << cls << " " << cls->name << "\n";
                auto found = visitorsMap.find(cls);

                if (found != end(visitorsMap)) {
                    std::cout << "VISITOR:     found handler...\n";

                    bool visitHandled = found->second(b);
                    // If visit was successfull, stop going through
                    // hierarchy and exit.
                    return !visitHandled;
                }
                std::cout << "VISITOR:     handler not found.\n";

                return true;
            }
        );
        return !neverVisited;
    }

    private:
        std::unordered_map<
            const ClassInfo*,
            std::function<bool(const Object& b)>
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
                const ClassInfo*, std::function<bool()>
            >& handlers
        ) : visitorsMap(handlers) {}

        bool visit(const ClassInfo* b) {
            std::cout << "STATIC VISITOR: Unwinding visit for class " << b->name << "\n";

            bool neverVisited = Hierarchy::instance()->destruct(
                b,
                [&] (const ClassInfo* cls) {
                    std::cout << std::hex
                    << "STATIC VISITOR:   Visiting class " << cls << " " << cls->name << "\n";
                    auto found = visitorsMap.find(cls);

                    if (found != end(visitorsMap)) {
                        std::cout << "STATIC VISITOR:     found handler...\n";

                        bool visitHandled = found->second();
                        // If visit was successfull, stop going through
                        // hierarchy and exit.
                        return !visitHandled;
                    }
                    std::cout << "STATIC VISITOR:     handler not found.\n";

                    return true;
                }
            );
            return !neverVisited;
        }

    private:
        std::unordered_map<const ClassInfo*, std::function<bool()>> visitorsMap;
    };
} // namespace myrtti
