#ifndef MYRTTI_DAG_H
#define MYRTTI_DAG_H

#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>

namespace myrtti {

template <typename NodeT>
struct DAG {
    /// @brief Adds class to hierarchyc
    /// @param cls class to be added
    /// @param parents parents list
    template <class ArrayT>
    void add(NodeT cls, ArrayT&& parents) {
        // TODO
    }

    /// @brief Checks child-parent relation
    /// @param child child class
    /// @param parent parent class
    /// @return true if relation is confirmed
    bool hasCommonPath(NodeT a, NodeT b) {
        throw std::logic_error("Not implemented.");
    }

    /// @brief Callback type for use with graph walking methods.
    using node_callback_t = std::function<bool(NodeT)>;

    /// @brief Deep first search from node to its predecessors.
    /// @param nd node the search starts from
    /// @param onNode is called for each visited node.
    /// @return true if search completed successfully and 'false' if it
    ///         was interrupted by callback.
    bool dfs(NodeT nd, const node_callback_t& onNode) {
        throw std::logic_error("Not implemented.");
    }

    /// @brief Breadth first search from node to its predecessors.
    /// @param nd node the search starts from
    /// @param onNode is called for each visited node.
    /// @return true if search completed successfully and 'false' if it
    ///         was interrupted by callback.
    bool bfs(NodeT nd, const node_callback_t& onNode) {
        throw std::logic_error("Not implemented.");
    }

private:
    std::unordered_set<NodeT> roots;
    std::unordered_map<NodeT, NodeT> edges;
};

} // namespace myrtti

#endif
