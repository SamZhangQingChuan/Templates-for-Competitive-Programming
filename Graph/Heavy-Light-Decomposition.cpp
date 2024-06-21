namespace HLD {
    //0不能被使用
    struct Edge {
        int to, len;
        
        Edge(int to, int len = 1) : to(to), len(len) {}
    };
    
    const int root = 1;
    const int maxn = 200010;
    vector<Edge> adj[maxn];
    int dfnToID[maxn], dfn[maxn], head[maxn], fa[maxn], size[maxn], heavy[maxn], r[maxn], cnt = 1;
    ll dep[maxn];
    
    void addEdge (int u, int v, int len = 1) {
        adj[u].emplace_back (v, len);
        adj[v].emplace_back (u, len);
    }
    
    void firstDfs(int cur, int _fa) {
        size[cur] = 1;
        fa[cur] = _fa;
        for(auto e:adj[cur]) {
            if(e.to != _fa) {
                dep[e.to] = dep[cur] + e.len;
                firstDfs(e.to, cur);
                size[cur] += size[e.to];
            }
        }
        int heavyChild = 0;
        for(auto e:adj[cur]) {
            if(e.to != _fa) {
                if(size[e.to] > size[heavyChild]) {
                    heavyChild = e.to;
                }
            }
        }
        heavy[cur] = heavyChild;
    }
    
    
    void secondDfs(int cur, int _fa) {
        if(cur != heavy[_fa]) {
            head[cur] = cur;
        } else {
            head[cur] = head[_fa];
        }
        dfn[cur] = cnt++;
        r[cur] = dfn[cur];
        dfnToID[dfn[cur]] = cur;
        if(!heavy[cur])return;
        secondDfs(heavy[cur], cur);
        r[cur] = r[heavy[cur]];
        for(auto e:adj[cur]) {
            if(e.to == _fa || e.to == heavy[cur])continue;
            secondDfs(e.to, cur);
            r[cur] = r[e.to];
        }
    }
    
    void init() {
        dep[1] = 0;
        firstDfs(root, 0);
        secondDfs(root, 0);
    }
    
    int kthFather(int k, int cur) {
        while(k) {
            if(head[cur] == cur) {
                k--;
                cur = fa[head[cur]];
            } else {
                if(dep[cur] - dep[head[cur]] <= k) {
                    k -= dep[cur] - dep[head[cur]];
                    cur = head[cur];
                } else {
                    return dfnToID[dfn[cur] - k];
                }
            }
        }
        return cur;
    }
    
    int LCA(int u, int v) {
        while(head[u] != head[v]) {
            if(dep[head[u]] > dep[head[v]])swap(u, v);
            v = fa[head[v]];
        }
        if(dep[u] < dep[v])return u;
        return v;
    }
    
    int dis(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[LCA(u, v)];
    }
    
    
    bool inSubtree(int root, int node) {
        return dfn[root] <= dfn[node] and dfn[node] <= r[root];
    }
}
