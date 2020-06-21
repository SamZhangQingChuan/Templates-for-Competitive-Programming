namespace CentroidDecomposition {
    const int maxn = 100010;
    
    int fa[maxn], siz[maxn];
    VI son[maxn];
    vector<PLL > adj[maxn];
    bool vis[maxn];
    
    
    void calc_size(int cur, int fa) {
        siz[cur] = 1;
        for(auto e:adj[cur]) {
            if(e.fi != fa and !vis[e.fi]) {
                calc_size(e.fi, cur);
                siz[cur] += siz[e.fi];
            }
        }
    }
    
    void find_center(int cur, int fa, const int tot, PII &center) {
        int max_siz = tot - siz[cur];
        for(auto e:adj[cur]) {
            if(e.fi != fa and !vis[e.fi]) {
                upmax(max_siz, siz[e.fi]);
                find_center(e.fi, cur, tot, center);
            }
        }
        upmin(center, MP(max_siz, cur));
    }
    
    
    int solve(int root) {
        calc_size(root, -1);
        PII center = MP(1e9, -1);
        find_center(root, -1, siz[root], center);
        vis[center.se] = true;
        for(auto e:adj[center.se]) {
            if(!vis[e.fi]) {
                int s = solve(e.fi);
                fa[s] = center.se;
                son[center.se].PB(s);
            }
        }
        return center.se;
    }
    
    void init() {
        mst(vis, 0);
        solve(1);
    }
    
    void update(int id) {
        for(int f = id; f != 0; f = fa[f]) {
        
        }
    }
}
