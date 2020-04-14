/*
 n,m,root:
 4 6 0
 from,to,weight:
 0 1 3
 0 2 2
 2 0 1
 2 3 1
 3 0 1
 3 1 5
 output:
 6
 */


// 0-indexed
// edges **leaves** the root
ll min_arborescence(ll n, ll root, vector <pair<PLL, ll>> edges) {
    DSU bcj;
    bcj.init(n);
    const ll MAX = 1e15;
    ll ans = 0;
    edges.erase(remove_if(all(edges), [&](pair <PLL, ll> a) { return a.fi.se == root; }), edges.end());
    while (true) {
        edges.erase(remove_if(all(edges), [&](pair <PLL, ll> a) { return a.fi.fi == a.fi.se; }), edges.end());
        vector <PLL> min_edge(n, MP(MAX, -1ll));
        vector <pair<PLL, ll>> new_edges;
        for (auto e:edges) {
            ll s = e.fi.fi, t = e.fi.se, w = e.se;
            upmin(min_edge[t], MP(w, s));
        }
        REP(i, 0, n)
        {
            if (i != root and bcj.root(i) == i and min_edge[i].fi == MAX) {
                return -1;
            }
        }
        for (auto &e:edges) {
            e.se -= min_edge[e.fi.se].fi;
        }
        REP(i, 0, n)
        {
            if (i != root and bcj.root(i) == i) {
                ans += min_edge[i].fi;
            }
        }
        vector<int> vis(n, -1);
        vis[root] = root;
        bool ok = true;
        REP(i, 0, n)
        {
            if (vis[i] != -1)continue;
            if (bcj.root(i) != i)continue;
            int id = i;
            int cur = i;
            while (vis[cur] == -1) {
                vis[cur] = id;
                cur = min_edge[cur].se;
            }
            if (cur == root or vis[cur] != id)continue;
            int start = cur;
            ok = false;
            do {
                bcj.unionSet(start, min_edge[start].se);
                start = min_edge[start].se;
            } while (start != cur);
        }
        if (ok)break;
        for (auto &e:edges) {
            e.fi.fi = bcj.root(e.fi.fi);
            e.fi.se = bcj.root(e.fi.se);
        }
    }
    return ans;
}
