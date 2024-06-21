#include <vector>


namespace CircleSquareTree {
    using ll = long long;
    using VLL = std::vector<ll>;

    struct Edge {
        ll from, to, id;

        Edge(ll from, ll to, ll id) : from(from), to(to), id(id) {}
    };


    const ll N = 500010 * 2; //开两倍

    ll low[N], dfn[N], cnt = 1, square;
    std::vector<Edge> adj[N];
    std::vector<Edge> stack;

    VLL realAdj[N]; // 点双树边

    void addRealEdge(int a, int b) {
        realAdj[a].push_back(b);
        realAdj[b].push_back(a);
    }

    void addEdge(int a, int b, int id) {
        adj[a].emplace_back(a, b, id);
        adj[b].emplace_back(b, a, id);
    }

    void tarjan(ll cur, Edge edge) {
        dfn[cur] = low[cur] = cnt++;
        for (auto e: adj[cur]) {
            if (e.id != edge.id) {
                auto to = e.to;
                if (!dfn[to]) {
                    stack.push_back(e);
                    tarjan(to, e);
                    upmin(low[cur], low[to]);
                    if (low[to] >= dfn[cur]) {
                        std::vector<Edge> components;
                        while (true) {
                            auto cur = stack.back();
                            stack.pop_back();
                            components.push_back(cur);
                            if (cur.id == e.id)break;
                        }
                        if (components.size() == 1) {
                            // bridge
                            addRealEdge(cur, e.to);
                        } else {
                            // bcc
                            auto center = square++;
                            for (auto edge: components) {
                                addRealEdge(center, edge.from);
                                addRealEdge(center, edge.to);
                            }
                        }
                    }
                } else {
                    upmin(low[cur], dfn[to]);
                }
            }
        }
    }

    // 圆方树在realAdj，编号为 [1,square)
    void run(int n, std::vector<PLL> edges) {
        fill(low, low + n + 1, 0);
        fill(dfn, dfn + n + 1, 0);
        cnt = 1, square = n + 1;
        REP(i, 0, (n + 1) * 2)
        adj[i].clear();
        REP(i, 0, (n + 1) * 2)
        realAdj[i].clear();
        stack.clear();
        REP(i, 0, sz(edges))
        {
            addEdge(edges[i].fi, edges[i].se, i);
        }
        tarjan(1, Edge(0, 0, -1));
        REP(i, 1, square)
        {
            sort(all(realAdj[i]));
            complete_unique(realAdj[i]);
        }
    }
}
