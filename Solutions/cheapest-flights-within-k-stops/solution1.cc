#include <vector>
#include <queue>
#include <utility>

using std::vector;

class Graph {
public:
    struct Edge {
        int node;
        int cost;
        
        Edge(int node, int cost) noexcept:
            node{node}, cost{cost}
        {}
    };
    
protected:
    std::vector<std::vector<Edge>> nodes;
    
public:
    Graph(int n, vector<vector<int>> &flights)
    {
        nodes.resize(n);
        
        for (auto &edges: flights) {
            int src = edges[0];
            int dst = edges[1];
            int cost = edges[2];
            
            nodes[src].emplace_back(dst, cost);
        }
        flights.clear();
        flights.shrink_to_fit();
        
        for (auto &node: nodes)
            node.shrink_to_fit();
    }
    
    /**
     * @return number of nodes
     */
    auto size() const noexcept
    {
        return nodes.size();
    }
    
    /**
     * @return vector of edges that start from node
     */
    auto& get_edges(int node) const noexcept
    {
        return nodes[node];
    }
};

struct FringeElement {
    int node;
    int g;
    int hops;
    
    FringeElement(int node, int g, int hops) noexcept:
        node{node}, g{g}, hops{hops}
    {}
    
    /**
     * std::priority_queue by default puts the biggest element at top,
     * so operator < will return true if y is smaller.
     */
    friend bool operator < (const FringeElement &x, const FringeElement &y)
    {
        return x.g > y.g;
    }
};
int UCS(const Graph &graph, int src, int dst, int K)
{
    std::priority_queue<FringeElement> pq;
    
    pq.emplace(src, 0, 0);
    
    while (pq.size() != 0) {
        const auto curr = pq.top();
        pq.pop();
        
        if (curr.node == dst)
            return curr.g;
        
        if (curr.hops > K)
            continue;
        
        for (const auto &edge: graph.get_edges(curr.node))
            pq.emplace(edge.node, curr.g + edge.cost, curr.hops + 1);
    }
    
    return -1;
}

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
         return UCS(Graph(n, flights), src, dst, K);
    }
};
