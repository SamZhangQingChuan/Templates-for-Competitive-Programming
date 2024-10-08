// 二分图最 "大" 权 "完美" 匹配，从 0 开始
// 不存在的边设成-inf
// sy[i] 表示 *右侧* 的 i 的对象
struct KM {
    typedef long long cost_t;
    static const int N = 1000;
    static constexpr cost_t inf = 1e9;
    cost_t lx[N], ly[N], sl[N];
    int px[N], py[N], sy[N], fa[N], n;
    
    void aug (int v) {
        sy[v] = py[v];
        if (px[sy[v]] != -2) aug (px[sy[v]]);
    }
    
    bool find (int v, const cost_t w[][N]) {
        for (int i = 0; i < n; ++i)
            if (!~py[i]) {
                if (sl[i] > lx[v] + ly[i] - w[v][i]) {
                    sl[i] = lx[v] + ly[i] - w[v][i];
                    fa[i] = v;
                }
                if (lx[v] + ly[i] == w[v][i]) {
                    py[i] = v;
                    if (!~sy[i]) {
                        aug (i);
                        return 1;
                    }
                    if (~px[sy[i]]) continue;
                    px[sy[i]] = i;
                    if (find (sy[i], w)) return 1;
                }
            }
        return 0;
    }
    
    cost_t gao (int _n, const cost_t w[][N], cost_t m = inf) {
        n = _n;
        std::fill (sy, sy + n, -1);
        std::fill (ly, ly + n, 0);
        for (int i = 0; i < n; ++i) lx[i] = *std::max_element (w[i], w[i] + n);
        for (int i (0), flag; i < n; ++i) {
            for (int j = 0; j < n; ++j)px[j] = py[j] = -1, sl[j] = inf;
            px[i] = -2;
            if (find (i, w)) continue;
            for (flag = 0, m = inf; !flag; m = inf) {
                for (int j = 0; j < n; ++j) if (!~py[j]) m = std::min (m, sl[j]);
                for (int j = 0; j < n; ++j) {
                    if (~px[j]) lx[j] -= m;
                    if (~py[j]) ly[j] += m;
                    else sl[j] -= m;
                }
                for (int j = 0; j < n; ++j)
                    if (!~py[j] && !sl[j]) {
                        py[j] = fa[j];
                        if (!~sy[j]) {
                            aug (j);
                            flag = 1;
                            break;
                        }
                        px[sy[j]] = j;
                        if (find (sy[j], w)) {
                            flag = 1;
                            break;
                        }
                    }
            }
        }
        cost_t ret (0);
        for (int i = 0; i < n; ++i) ret += w[sy[i]][i];
        return ret;
    }
} km;
