#include "bits/stdc++.h"
using namespace std;

struct graph {
    int n;
    vector<vector<int>> adj;
    
    graph(int n) : n(n), adj(n) {}
    
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    int add_node() {
        adj.push_back({});
        return n++;
    }
    
    vector<int> &operator[](int u) { return adj[u]; }
};

pair<vector<int>, pair<graph, vector<int>>> biconnected_components(graph &adj) {
    int n = adj.n;
    
    vector<int> num(n), low(n), art(n), stk;
    vector<vector<int>> comps;
    
    function<void(int, int, int &)> dfs = [&](int u, int p, int &t) {
        num[u] = low[u] = ++t;
        stk.push_back(u);
        
        for(int v : adj[u])
            if(v != p) {
                if(!num[v]) {
                    dfs(v, u, t);
                    low[u] = min(low[u], low[v]);
                    
                    if(low[v] >= num[u]) {
                        art[u] = (num[u] > 1 || num[v] > 2);
                        
                        comps.push_back({u});
                        while(comps.back().back() != v)
                            comps.back().push_back(stk.back()), stk.pop_back();
                    }
                } else low[u] = min(low[u], num[v]);
            }
    };
    
    for(int u = 0, t; u < n; ++u)
        if(!num[u]) dfs(u, -1, t = 0);
    
    // build the block cut tree
    function<pair<vector<int>, pair<graph, vector<int>>>()> build_tree = [&]() {
        graph tree(0);
        vector<int> id(n);
        
        for(int u = 0; u < n; ++u)
            if(art[u]) id[u] = tree.add_node();
        
        for(auto &comp : comps) {
            int node = tree.add_node();
            for(int u : comp)
                if(!art[u]) id[u] = node;
                else tree.add_edge(node, id[u]);
        }
        
        return make_pair(art, make_pair(tree, id));
    };
    
    return build_tree();
}
