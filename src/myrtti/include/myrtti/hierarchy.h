#ifndef MYRTTI_HIERARCHY_H
#define MYRTTI_HIERARCHY_H

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "myrtti/class_id.h"
#include "myrtti/dag.h"

namespace myrtti {

struct ClassInfo;
template <typename NodeT> struct DAG;

struct Hierarchy {

    /// @brief Adds class to hierarchy
    /// @param cls class to be added
    /// @param parents parents list
    template<typename ArrayT>
    void add(const ClassInfo *cls, const ArrayT& parents) {

        // TODO: first move this into .cpp, then add class_id validation.
        //
        // auto [it, added] = added_clids.insert(cls->getId());
        // if (!added) {
        //     std::ostringstream strm;
        //     strm << "Class " << cls
        //          << " has colliding id. Unable to maintain hierarchy"
        //          << " consider changing CRC initial state."
        //     throw std::runtime_error(strm.str());
        // }

        constexpr std::size_t numParents = parents.size();
        std::array<class_id_t, numParents> parentIds;
        for (std::size_t i = 0; i!=numParents;++i) {
            parentIds[i] = parents[i]->getId();
        }

        dag.add(cls, parents);
        idToClass[cls->getId()] = cls;

        // Get ancestors cache for O(0) 'isParent' implementation.
        // tradeof: RAM consumption N^2 (N amount of classes)
        if (!parents.empty()) {
            auto [it, _] = ancestorsCache.emplace(cls, classes_set_t());
            auto &ancestors = it->second;

            for (auto p : parents) {
                auto &pAncestors = ancestorsCache[p];
                ancestors.insert(begin(pAncestors), end(pAncestors));
            }
            ancestors.insert(begin(parents), end(parents));
        }
    }

    /// @brief Checks child-parent relation.
    /// NOTE: this is a duplicated feature of Object::cast<T>
    ///   the latter applicable for <instance, another class> pair,
    ///   whilst the former applicable for pure <ClassInfo, ClassInfo> pair.
    ///
    /// @param child child class ID
    /// @param parent parent class ID
    /// @return true if relation is confirmed
    bool isParent(class_id_t child, class_id_t parent) {
        return ancestorsCache.count(child)
            && ancestorsCache[child].count(parent);
    }

    /// @brief Callback type for use with hierarchy walking methods.
    using node_callback_t = std::function<bool(const ClassInfo *)>;

    /// @brief Invokes custom callback follwing classes as it would call
    /// constructors.
    /// @param cls cls the search starts from
    /// @param onNode node callback.
    /// @return true if search completed successfully and 'false' if it
    ///         was interrupted by callback.
    bool construct(class_id_t clsid, const node_callback_t& onNode) {
        return dag.dfs(clsid,
            /*onBeforeNode*/ nullptr,
            /*onAfterNode*/ [&](class_id_t traversedClsId) {
                const ClassInfo* traversedCls = idToClass[traversedClsId];
                return onNode(traversedCls);
            }
        );
    }

    /// @brief Invokes custom callback follwing classes as it would call
    /// destructors.
    /// @param cls cls the search starts from
    /// @param onNode node callback.
    /// @return true if search completed successfully and 'false' if it
    ///         was interrupted by callback.
    bool destruct(class_id_t clsid, const node_callback_t& onNode) {
        return dag.dfs(clsid,
            /*onBeforeNode*/ [&](class_id_t traversedClsId) {
                const ClassInfo* traversedCls = idToClass[traversedClsId];
                return onNode(traversedCls);
            }
        );
    }

    Hierarchy& operator=(const Hierarchy& src) = delete;

    static Hierarchy* instance() {
        static Hierarchy h;
        return &h;
    }

private:
    // TODO: in order to reduce compile time impact we could
    // move out direct DAG template usage into .cpp file.
    // We can do it through HierarchyImpl which will be defined
    // in .cpp. It allows to declare DAG template in .cpp, thus reducing
    // complexity of task for those who will use header.
    // With high probability this impl will be inlined by compiler
    // optimizations.
    // As an alternative we can use shared_ptr, but it might be slower.
    // std::shared_ptr<DAG<const ClassInfo*>> dag;
    DAG<class_id_t> dag;

    // FIXME: Unable to use ClassInfo complete type due to cycled deps, see
    // previous comment to move some code into .cpp and then
    // apply code below:
    // std::unordered_set<class_id_t, class_id_t::hash> added_clids;


    // TODO: consider using class_id_t instead.
    using classes_map_t = std::unordered_map<class_id_t, const ClassInfo*>;
    using classes_set_t = std::unordered_set<class_id_t>;

    classes_map_t idToClass;
    std::unordered_map<class_id_t, classes_set_t> ancestorsCache;
};

} // namespace myrtti

#endif