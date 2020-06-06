// 0-indexed [0..n-1]
namespace EulerPath {
    const bool UNDIRECTED =;
    
    struct Edge {
        int from, to;
        list<Edge>::iterator rev;
        
        Edge (int from, int to) : from (from), to (to) {}
    };
    
    const int N = 1000010;
    list<Edge> adj[N];
    vector<Edge> path; // our result
    int inDeg[N];
    
    void find_path (int v) {
        while (adj[v].size () > 0) {
            auto edge = adj[v].front ();
            int vn = adj[v].front ().to;
            if (UNDIRECTED)adj[vn].erase (adj[v].front ().rev);
            adj[v].pop_front ();
            find_path (vn);
            path.push_back (edge);
        }
    }
    
    
    int getSource (int n, int default_source) {
        if (UNDIRECTED) {
            REP(i, 0, n) {
                if (sz(adj[i]) % 2 == 1)return i;
            }
            REP(i, 0, n) {
                if (sz(adj[i]))return i;
            }
        } else {
            fill (inDeg, inDeg + n, 0);
            REP(i, 0, n) {
                for (auto e:adj[i])inDeg[e.to]++;
            }
            REP(i, 0, n) {
                if (sz(adj[i]) > inDeg[i])return i;
            }
            REP(i, 0, n) {
                if (sz(adj[i]))return i;
            }
        }
        return default_source;
    }
    
    
    bool verify (int n, int m) {
        if (sz(path) != m)return false;
        for (int i = 1; i < m; i++) {
            if (path[i].from != path[i - 1].to)return false;
        }
        return true;
    }
    
    
    void addEdge (int a, int b) {
        adj[a].push_front (Edge (a, b));
        auto ita = adj[a].begin ();
        if (UNDIRECTED) {
            adj[b].push_front (Edge (b, a));
            auto itb = adj[b].begin ();
            ita->rev = itb;
            itb->rev = ita;
        }
    }
    
    
    void init (int n, int m) {
        REP(i, 0, n)adj[i].clear ();
        path.clear ();
        REP(i, 0, m) {
            int a, b;
            cin>>a>>b;
            addEdge (a, b);
        }
    }
    
    
    void work (int n, int m) {
        init (n, m);
        int source = getSource (n, n - 1);
        find_path (source);
        reverse (all(path));
        if (!verify (n, m)) {
            cout<<"No solution"<<endl;
        } else {
            // output solution
        }
    }
}
