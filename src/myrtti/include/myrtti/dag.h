#ifndef MYRTTI_DAG_H
#define MYRTTI_DAG_H

#include <cassert>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include <vector>

namespace myrtti {

template <typename NodeIdT>
struct DAG {
    /// @brief Adds class to hierarchy
    /// @param cls class to be added
    /// @param parents parents list
    template <class ArrayT>
    void add(NodeIdT cls, const ArrayT& parents) {

        auto [it, inserted] =  nodes.insert(cls);
        assert(inserted && "We can add each node only once.");

        if (parents.empty()) {
            roots.insert(cls);
        } else {
            incomingEdges.emplace(cls, nodes_list_t(begin(parents), end(parents)));
        }
    }

    /// @brief Callback type for use with graph walking methods.
    using node_callback_t = std::function<bool(NodeIdT)>;

    /// @brief Deep first search from node to its predecessors.
    /// @param startNode node the search starts from
    /// @param onNode is called for each visited node.
    /// @return true if search completed successfully and 'false' if it
    ///         was interrupted by callback.
    bool dfs(NodeIdT startNode, const node_callback_t& onNode) {
        throw std::logic_error("Not implemented.");
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

    nodes_set_t nodes;
    nodes_set_t roots;

    /// @brief collection of incoming edges for node privided as a key.
    std::unordered_map<NodeIdT, nodes_list_t> incomingEdges;
};

} // namespace myrtti

#endif
