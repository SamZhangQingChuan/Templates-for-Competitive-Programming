namespace maxFlow {
    const ll maxn = 10010, maxe = 40010, source = maxn - 1, sink = maxn - 2;
    ll cnt = 0;
    
    struct edge {
        ll from, to, cap;
        
        edge(ll a, ll b, ll c) : from(a), to(b), cap(c) {}
        
        edge() {
            from = to = cap = 0;
        }
    };
    
    vector <ll> g[maxn];
    edge e[maxe];
    
    void clear() {
        cnt = 0;
        REP(i, 0, maxn)
        g[i].clear();
        REP(i, 0, maxe)
        e[i] = edge();
    }
    
    void addEdge(ll u, ll v, ll cap) {
        ll cur = cnt;
        e[cur] = edge(u, v, cap);
        g[u].PB(cur);
        e[cur ^ 1] = edge(v, u, 0);
        g[v].PB(cur ^ 1);
        cnt += 2;
    }
    
    ll lvl[maxn], cur[maxn];
    
    bool bfs(ll start = source) {
        mst(lvl, -1);
        mst(cur, 0);
        lvl[start] = 0;
        queue <ll> q;
        q.push(start);
        
        while (sz(q)) {
            ll f = q.front();
            q.pop();
            for (auto curEdge:g[f]) {
                auto &E = e[curEdge];
                if (E.cap) {
                    if (lvl[E.to] == -1) {
                        lvl[E.to] = lvl[f] + 1;
                        q.push(E.to);
                    }
                }
            }
        }
        
        return lvl[sink] != -1;
    }
    
    
    ll dfs(ll curNode, ll curCap) {
        if (!curCap || curNode == sink)return curCap;
        ll ans = 0;
        for (ll &i = cur[curNode]; i < sz(g[curNode]); i++) {
            ll curEdge = g[curNode][i];
            if (lvl[e[curEdge].to] > lvl[curNode]) {
                ll delta = dfs(e[curEdge].to, min(e[curEdge].cap, curCap));
                ans += delta;
                curCap -= delta;
                e[curEdge].cap -= delta;
                e[curEdge ^ 1].cap += delta;
                if (!curCap)break;
            }
        }
        return ans;
    }
    
    ll dinic() {
        ll ans = 0;
        while (bfs()) {
            ans += (dfs(source, inf));
        }
        return ans;
    }
}

