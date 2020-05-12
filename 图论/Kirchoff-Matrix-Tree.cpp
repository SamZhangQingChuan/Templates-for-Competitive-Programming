int count_spanning_tree(vector <PII> edges, int mod) {
    DSU connectivity;
    vector<int> nodes;
    for (auto e:edges) {
        nodes.PB(e.fi);
        nodes.PB(e.se);
    }
    sort(all(nodes));
    complete_unique(nodes);
    vector <VI> mat;
    REP(i, 0, sz(nodes))
    {
        mat.PB(VI(sz(nodes), 0));
    }
    connectivity.init(sz(nodes));
    for (auto e:edges) {
        e.fi = LB(all(nodes), e.fi) - nodes.begin();
        e.se = LB(all(nodes), e.se) - nodes.begin();
        connectivity.unionSet(e.fi, e.se);
        mat[e.fi][e.fi]++;
        mat[e.se][e.se]++;
        mat[e.fi][e.se]--;
        mat[e.se][e.fi]--;
    }
    REP(i, 0, sz(nodes))
    {
        if (!connectivity.same(i, 0)) {
            connectivity.unionSet(i, 0);
            mat[i][0]--;
            mat[0][i]--;
            mat[i][i]++;
            mat[0][0]++;
        }
    }
    return det_mod(sz(nodes) - 1, mod, mat);
}

int count_minimum_spanning_tree(vector <pair<int, PII>> edges, int mod) {
    const int maxn = 1010;
    DSU bcj;
    bcj.init(maxn);
    ll ans = 1;
    sort(all(edges), greater < pair < int, PII > > ());
    while (sz(edges)) {
        vector <PII> current_edges;
        int val = edges.back().fi;
        while (sz(edges) and edges.back().fi == val) {
            auto e = edges.back().se;
            e.fi = bcj.root(e.fi);
            e.se = bcj.root(e.se);
            current_edges.PB(e);
            edges.pop_back();
        }
        
        for (auto e:current_edges)bcj.unionSet(e.fi, e.se);
        ans *= count_spanning_tree(current_edges, mod);
        ans %= mod;
    }
    return ans;
}
