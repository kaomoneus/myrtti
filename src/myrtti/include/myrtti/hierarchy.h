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
        dag.add(cls, parents);


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
    /// NOTE: this is a duplicated feature of RTTIMeta::cast<T>
    ///   the latter applicable for <instance, another class> pair,
    ///   whilst the former applicable for pure <ClassInfo, ClassInfo> pair.
    ///
    /// @param child child class
    /// @param parent parent class
    /// @return true if relation is confirmed
    bool isParent(const ClassInfo *child, const ClassInfo *parent) {
        return ancestorsCache.count(child)
            && ancestorsCache[child].count(parent);
    }

    /// @brief Callback type for use with hierarchy walking methods.
    using node_callback_t = std::function<bool(const ClassInfo *)>;

    /// @brief Deep first search from class to its ancestors.
    /// Might be usefull for constructor-like calls, for constructors
    /// should be called from ancestors to current class.
    /// @param cls cls the search starts from
    /// @param onNode is called for each node.
    /// @return true if search completed successfully and 'false' if it
    ///         was interrupted by callback.
    bool contruct(const ClassInfo *cls, const node_callback_t& onNode) {
        return dag.dfs(cls, onNode);
    }

    /// @brief Breadth first search from class to its ancestors.
    /// Might be usefull for destructor-like calls, since destructors
    /// are calling from current class, down to ancestors.
    /// @param cls cls the search starts from
    /// @param onNode is called for each node.
    /// @return true if search completed successfully and 'false' if it
    ///         was interrupted by callback.
    bool destruct(const ClassInfo* cls, const node_callback_t& onNode) {
        return dag.bfs(cls, onNode);
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
    // in .cpp and will store DAG instead of Hierarchy itself.
    // With high probability this impl will be inlined by compiler
    // optimizations.
    // As an alternative we can use shared_ptr, but it might be slower.
    // std::shared_ptr<DAG<const ClassInfo*>> dag;
    DAG<const ClassInfo*> dag;

    using classes_set_t = std::unordered_set<const ClassInfo*>;

    std::unordered_map<const ClassInfo*, classes_set_t> ancestorsCache;
};

} // namespace myrtti

#endif