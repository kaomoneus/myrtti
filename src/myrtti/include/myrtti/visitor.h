#include "myrtti/runtime.h"
#include "myrtti/hierarchy.h"

#include <functional>
#include <unordered_map>

namespace rtti
{
    /// @brief Implements a visitor pattern which visits const references.
    struct VisitorConst {
        template<class Cls...>
        VisitorConst(std::function<bool(const Cls& inst)> ...visitors) {
            (
                [&] {
                    visitorsMap.emplace(
                        &Cls::info(),
                        [&] (const Object& b) {
                            return visitors(static_cast<const Cls&>(b));
                        }
                    );
                } (), ...
            );
        }

    bool visit(const Object& b, bool notFoundResult = true) {
        auto found = visitorsMap.find(b.rtti);
        if (found != end(visitorsMap))
            return found->second(b);
        return notFoundResult;
    }

    private:
        std::unordered_map<
            const ClassInfo*,
            std::function<bool(const Object& b)>
        > visitorsMap;
    }
} // namespace rtti
