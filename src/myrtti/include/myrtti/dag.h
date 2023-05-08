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

#ifndef MYRTTI_DAG_H
#define MYRTTI_DAG_H

#include <algorithm>
#include <cassert>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

namespace myrtti {

template <typename NodeIdT>
struct DAG {
    /// @brief Adds class to hierarchy
    /// @param cls class to be added
    /// @param parents parents list
    template <class ArrayT>
    bool add(NodeIdT cls, const ArrayT& parents) {

        auto [it, inserted] =  nodes.insert(cls);
        if (!inserted)
            return false;

        if (parents.empty()) {
            roots.insert(cls);
        } else {
            incomingEdges.emplace(cls, nodes_list_t(begin(parents), end(parents)));
        }
        return true;
    }

    /// @brief Callback type for use with graph walking methods.
    using node_callback_t = std::function<bool(NodeIdT)>;

    /// @brief Deep first search from node to its predecessors.
    /// @param startNode node the search starts from
    /// @param onBeforeNode is called for each node before recursive deepings.
    /// @param onAfterNode is called for each node after all subsequent
    ///        nodes have been visited.
    ///        If during subsequent nodes the search is canceled this
    ///        callback IS NOT INVOKED.
    /// @param reversiveSideWalk true then we walk direct parents from last
    ///        to first.
    /// @return true if search completed successfully and 'false' if it
    ///         was interrupted by callback.
    bool dfs(
        NodeIdT startNode,
        const node_callback_t& onBeforeNode,
        const node_callback_t& onAfterNode = nullptr,
        bool reversiveSideWalk = false
    ) const {
        nodes_set_t visited;

        if (/* [[likely]] */ !reversiveSideWalk)
            return dfsRecursive(
                visited, startNode,
                &nodes_list_t::cbegin, &nodes_list_t::cend,
                onBeforeNode, onAfterNode
            );
        else {
            return dfsRecursive(
                visited, startNode,
                &nodes_list_t::crbegin, &nodes_list_t::crend,
                onBeforeNode, onAfterNode
            );
        }
    }

    /// @brief Breadth first search from node to its predecessors.
    /// @param nd node the search starts from
    /// @param onNode is called for each visited node.
    /// @return true if search completed successfully and 'false' if it
    ///         was interrupted by callback.
    bool bfs(NodeIdT startNode, const node_callback_t& onNode) {
        nodes_set_t visited;
        nodes_list_t wl{startNode};

        while (wl.empty()) {
            nodes_list_t wl2;
            for (auto nd : wl) {
                auto [_, inserted] = visited.insert(nd);
                if (!inserted) continue;

                if (!onNode(nd))
                    return false;

                if (roots.count(nd))
                    continue;

                const auto& incoming = incomingEdges[nd];

                wl2.insert(end(wl2), begin(incoming), end(incoming));
            }
            wl.swap(wl2);
        }

        return true;
    }

private:

    using nodes_list_t = std::vector<NodeIdT>;
    using nodes_set_t = std::unordered_set<NodeIdT>;

    template <typename ItPtrs>
    bool dfsRecursive(
        nodes_set_t &visited,
        NodeIdT curNode,
        ItPtrs beginPtr,
        ItPtrs endPtr,
        const node_callback_t& onBeforeNode,
        const node_callback_t& onAfterNode = nullptr
    ) const {
        auto [_, inserted] = visited.insert(curNode);
        if (!inserted)
            return true;

        if (onBeforeNode && !onBeforeNode(curNode))
            return false;

        auto incomingIt = incomingEdges.find(curNode);
        if (incomingIt != end(incomingEdges)) {

            const auto& incoming = incomingIt->second;

            auto beginF = std::bind(beginPtr, &incoming);
            auto endF = std::bind(endPtr, &incoming);

            for (auto i = beginF(), e = endF(); i!=e; ++i) {
                NodeIdT p = *i;
                if (!dfsRecursive(visited, p, beginPtr, endPtr, onBeforeNode, onAfterNode))
                    return false;
            }
        }

        if (onAfterNode && !onAfterNode(curNode))
            return false;

        return true;
    };

    nodes_set_t nodes;
    nodes_set_t roots;

    /// @brief collection of incoming edges for node privided as a key.
    std::unordered_map<NodeIdT, nodes_list_t> incomingEdges;
};

} // namespace myrtti

#endif
