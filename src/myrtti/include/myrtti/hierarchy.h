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

#ifndef MYRTTI_HIERARCHY_H
#define MYRTTI_HIERARCHY_H

#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
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
    void add(const ClassInfo *cls, const ArrayT& parentIds) {

        auto clsId = resolveClassInfoId(cls);

        dag.add(clsId, parentIds);

        auto [it, added] = idToClass.emplace(clsId, cls);
        if (!added) {
            std::ostringstream strm;
            strm << "Class " << cls
                 << " has colliding id. Unable to maintain hierarchy"
                 << " consider changing class name or CRC64 initial state.";
            throw std::runtime_error(strm.str());
        }

        // Get ancestors cache for O(0) 'isParent' implementation.
        // tradeof: RAM consumption N^2 (N amount of classes)
        if (!parentIds.empty()) {
            auto [it, _] = ancestorsCache.emplace(clsId, classes_set_t());
            auto &ancestors = it->second;

            for (auto p : parentIds) {
                auto &pAncestors = ancestorsCache[p];
                ancestors.insert(begin(pAncestors), end(pAncestors));
            }
            ancestors.insert(begin(parentIds), end(parentIds));
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

    /// @brief Resolves ClassInfo by given class_id.
    /// @param clsid class_id instance to be resolved for
    /// @return ClassInfo pointer or nullptr is there is no such class
    //          registered.
    const ClassInfo* getClassInfo(class_id_t clsid) const {
        auto found = idToClass.find(clsid);
        if (found != end(idToClass))
            return found->second;

        return nullptr;
    }

    Hierarchy& operator=(const Hierarchy& src) = delete;

    static Hierarchy* instance() {
        static Hierarchy h;
        return &h;
    }

private:

    /// @brief Picks classInfo->getId(), where classInfo is a pointer to
    /// incomplete class.
    ///
    /// This is a helper method to prevent circular dependency
    /// between ClassInfo and Hierarchy. In this header we only can use
    /// incomplete ClassInfo. And in order to call one of its methods
    /// we should move it to .cpp part.
    /// @param classInfo - ClassInfo pointer
    /// @return class_id for given classInfo.
    static class_id_t resolveClassInfoId(const ClassInfo* classInfo);

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

    using classes_map_t = std::unordered_map<class_id_t, const ClassInfo*>;
    using classes_set_t = std::unordered_set<class_id_t>;

    classes_map_t idToClass;
    std::unordered_map<class_id_t, classes_set_t> ancestorsCache;
};

} // namespace myrtti

#endif