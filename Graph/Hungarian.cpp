#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct hungarian {  // km
    int n;
    vector<int> matchx;
    vector<int> matchy;
    vector<int> pre;
    vector<bool> visx;
    vector<bool> visy;
    vector<T> lx;
    vector<T> ly;
    vector<vector<T> > g;
    vector<T> slack;
    T inf;
    T res;
    queue<int> q;

    hungarian(int _n, int _m) {
        n = max(_n, _m);
        inf = numeric_limits<T>::max();
        res = 0;
        g = vector<vector<T> >(n, vector<T>(n));
        matchx = vector<int>(n, -1);
        matchy = vector<int>(n, -1);
        pre = vector<int>(n);
        visx = vector<bool>(n);
        visy = vector<bool>(n);
        lx = vector<T>(n, -inf);
        ly = vector<T>(n);
        slack = vector<T>(n);
    }

    void addEdge(int u, int v, T w) {
        assert(w >= 0);
        g[u][v] = w;
    }

    bool check(int v) {
        visy[v] = true;
        if (matchy[v] != -1) {
            q.push(matchy[v]);
            visx[matchy[v]] = true;
            return false;
        }
        while (v != -1) {
            matchy[v] = pre[v];
            swap(v, matchx[pre[v]]);
        }
        return true;
    }

    void bfs(int i) {
        while (!q.empty()) {
            q.pop();
        }
        q.push(i);
        visx[i] = true;
        while (true) {
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v = 0; v < n; v++) {
                    if (!visy[v]) {
                        T delta = lx[u] + ly[v] - g[u][v];
                        if (slack[v] >= delta) {
                            pre[v] = u;
                            if (delta) {
                                slack[v] = delta;
                            } else if (check(v)) {
                                return;
                            }
                        }
                    }
                }
            }
            // 没有增广路 修改顶标
            T a = inf;
            for (int j = 0; j < n; j++) {
                if (!visy[j]) {
                    a = min(a, slack[j]);
                }
            }
            for (int j = 0; j < n; j++) {
                if (visx[j]) {  // S
                    lx[j] -= a;
                }
                if (visy[j]) {  // T
                    ly[j] += a;
                } else {  // T'
                    slack[j] -= a;
                }
            }
            for (int j = 0; j < n; j++) {
                if (!visy[j] && slack[j] == 0 && check(j)) {
                    return;
                }
            }
        }
    }

    void solve() {
        // 初始顶标
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                lx[i] = max(lx[i], g[i][j]);
            }
        }

        for (int i = 0; i < n; i++) {
            fill(slack.begin(), slack.end(), inf);
            fill(visx.begin(), visx.end(), false);
            fill(visy.begin(), visy.end(), false);
            bfs(i);
        }
    }
};
