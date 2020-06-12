namespace BipolarOrientation {
    const ll N = 500010;
    VLL adj[N], tree[N];
    ll n, m;
    list<int> order;
    list<int>::iterator ptr[N];
    ll dfn[N], low[N], dfnToID[N], cnt = 1;
    int sign[N];
    
    
    void dfs (int cur, int fa) {
        dfn[cur] = low[cur] = cnt++;
        dfnToID[dfn[cur]] = cur;
        for (auto nxt:adj[cur]) {
            if (nxt == fa)continue;
            if (!dfn[nxt]) {
                dfs (nxt, cur);
                tree[cur].PB (nxt);
                upmin (low[cur], low[nxt]);
            } else {
                upmin (low[cur], dfn[nxt]);
            }
        }
    }
    
    
    void dfs2 (int cur, int fa) {
        dbg(cur, fa);
        if (cur != order.front () and cur != order.back ()) {
            if (sign[dfnToID[low[cur]]]) {
                ptr[cur] = order.insert (ptr[fa], cur);
            } else {
                ptr[cur] = order.insert (next (ptr[fa]), cur);
            }
            sign[fa] = !sign[dfnToID[low[cur]]];
        }
        for (auto nxt:tree[cur]) {
            dfs2 (nxt, cur);
        }
    }
    
    
    void clean () {
        cnt = 1;
        order.clear ();
        fill (sign, sign + n + 1, 0);
        fill (low, low + n + 1, 0);
        fill (dfn, dfn + n + 1, 0);
        fill (dfnToID, dfnToID + n + 1, 0);
        fill (tree, tree + n + 1, VLL ());
        fill (adj, adj + n + 1, VLL ());
    }
    
    void construct (int s, int t) {
        sign[s] = true;
        adj[s].insert (begin (adj[s]), t);
        adj[t].insert (begin (adj[t]), s);
        order.push_back (s);
        ptr[s] = prev (order.end ());
        order.push_back (t);
        ptr[t] = prev (order.end ());
        dfs (s, 0);
        dfs2 (s, 0);
        for (auto i:order)cout<<i<<" ";
    }
    
    void main (int _n, vector<PLL > edges, int s, int t) {
        n = _n;
        m = sz(edges);
        clean ();
        for (auto e:edges) {
            adj[e.fi].PB (e.se);
            adj[e.se].PB (e.fi);
        }
        construct (s, t);
    }
}
