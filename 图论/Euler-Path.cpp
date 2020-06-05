// - When choosing starting vertex (for calling find_path), make sure deg[start] > 0.
// - If find Euler path, starting vertex must have odd degree.
// - Check no solution: SZ(path) == nEdge + 1.
//
// Tested:
// - https://open.kattis.com/problems/eulerianpath (directed)
// - SGU 101 (undirected).
//
// If directed:
// - Edge --> int
// - add_edge(int a, int b) { adj[a].push_back(b); }
// - set the source
// - Check for no solution:
// - - for all u, |in_deg[u] - out_deg[u]| <= 1
// - - At most 1 vertex with in_deg[u] - out_deg[u] = 1
// - - At most 1 vertex with out_deg[u] - in_deg[u] = 1 (start vertex)
// - - BFS from start vertex, all vertices u with out_deg[u] > 0 must be visited
// - Check validity after run
namespace EulerPath {
    const bool UNDIRECTED = 0;
    const int DEFAULT_SOURCE = 0;
    
    struct Edge {
        int to;
        list<Edge>::iterator rev;
        
        Edge (int to) : to (to) {}
    };
    
    const int N = 2000010;
    list<Edge> adj[N];
    vector<Edge> path; // our result
    int deg[N];
    
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
    
    void add_edge (int a, int b) {
        adj[a].push_front (Edge (b));
        auto ita = adj[a].begin ();
        if (UNDIRECTED) {
            adj[b].push_front (Edge (a));
            auto itb = adj[b].begin ();
            ita->rev = itb;
            itb->rev = ita;
        }
    }
    
    
    enum State {
        CIRCUIT,
        PATH,
        IMPOSSIBLE
    };
    
    pair<State, int> test (const int n) {
        if (UNDIRECTED) {
            int cnt = 0;
            REP(i, 0, n) {
                cnt += (deg[i] % 2);
            }
            if (cnt == 0) {
                REP(i, 0, n) {
                    if (sz(adj[i]) > 0) {
                        return MP (CIRCUIT, i);
                    }
                }
                return MP (CIRCUIT, DEFAULT_SOURCE);
            } else if (cnt == 2) {
                REP(i, 0, n) {
                    if (sz(adj[i]) % 2 != 0) {
                        return MP (PATH, i);
                    }
                }
                return MP (CIRCUIT, DEFAULT_SOURCE);
            } else {
                return MP (IMPOSSIBLE, DEFAULT_SOURCE);
            }
            
        } else {
            fill (deg, deg + n, 0);
            REP(i, 0, n) {
                for (auto e:adj[i]) {
                    deg[i]++;
                    deg[e.to]--;
                }
            }
            int src = -1;
            REP(i, 0, n) {
                if (deg[i] > 0) {
                    if (src == -1) {
                        src = i;
                    } else {
                        return MP (IMPOSSIBLE, DEFAULT_SOURCE);
                    }
                }
            }
            if (src == -1) {
                REP(i, 0, n) {
                    if (sz(adj[i]) > 0) {
                        return MP (CIRCUIT, i);
                    }
                }
                return MP (CIRCUIT, DEFAULT_SOURCE);
            } else {
                return MP (PATH, src);
            }
        }
    }
    
    void init (int n, int m) {
        REP(i, 0, n + 1)adj[i].clear ();
        path.clear ();
        REP(i, 0, m) {
            int a, b;
            cin>>a>>b;
            add_edge (a, b);
        }
    }
    
    void work (int n, int m) {
        //add edge
        init (n, m);
        auto type = test (n);
        int source = type.se;
        if (type.fi == IMPOSSIBLE) {
            cout<<"Impossible"<<endl;
            return;
        }
        find_path (source);
        reverse (all(path));
        if (sz(path) != m) {
            cout<<"Impossible"<<endl;
        } else {
            if (m) {
                cout<<source<<" ";
                for (auto e:path)cout<<e.to<<" ";
            }
            cout<<endl;
        }
    }
}