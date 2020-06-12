namespace CircleSquareTree {
    struct Edge {
        ll from, to, id;
        
        Edge (ll from, ll to, ll id) : from (from), to (to), id (id) {}
    };
    
    
    const ll N = 200010;
    
    ll low[N], dfn[N], cnt = 1, square;
    vector<Edge> adj[N];
    vector<Edge> stack;
    
    VLL realAdj[N]; // 点双树边
    
    void addRealEdge (int a, int b) {
        realAdj[a].PB (b);
        realAdj[b].PB (a);
    }
    
    void addEdge (int a, int b, int id) {
        adj[a].PB (Edge (a, b, id));
        adj[b].PB (Edge (b, a, id));
    }
    
    void tarjan (ll cur, Edge edge) {
        dfn[cur] = low[cur] = cnt++;
        for (auto e:adj[cur]) {
            if (e.id != edge.id) {
                auto to = e.to;
                if (!dfn[to]) {
                    stack.PB (e);
                    tarjan (to, e);
                    upmin (low[cur], low[to]);
                    if (low[to] >= dfn[cur]) {
                        vector<Edge> components;
                        while (true) {
                            auto cur = stack.back ();
                            stack.pop_back ();
                            components.PB (cur);
                            if (cur.id == e.id)break;
                        }
                        if (sz(components) == 1) {
                            // bridge
                            addRealEdge (cur, e.to);
                        } else {
                            // bcc
                            auto center = square++;
                            for (auto edge:components) {
                                addRealEdge (center, edge.from);
                                addRealEdge (center, edge.to);
                            }
                        }
                    }
                } else {
                    upmin (low[cur], dfn[to]);
                }
            }
        }
    }
    
    
    void run (int n, vector<PLL > edges) {
        mst(low, 0);
        mst(dfn, 0);
        cnt = 1, square = n + 1;
        REP(i, 0, N)adj[i].clear ();
        REP(i, 0, N)realAdj[i].clear ();
        stack.clear ();
        REP(i, 0, sz (edges)) {
            addEdge (edges[i].fi, edges[i].se, i);
        }
        tarjan (1, Edge (0, 0, -1));
        REP(i, 1, square) {
            sort (all(realAdj[i]));
            complete_unique(realAdj[i]);
            dbg(realAdj[i]);
        }
    }
}
