#include <bits/stdc++.h>
#define M 200010

using namespace std;

int node_cnt, n, m;
int sum[M << 5], rt[M], lc[M << 5], rc[M << 5];//线段树相关
int a[M], b[M];//原序列和离散序列
int p;//修改点

void build(int &t, int l, int r) {
    t = ++node_cnt;
    if(l == r)
        return;
    int mid = (l + r) >> 1;
    build(lc[t], l, mid);
    build(rc[t], mid + 1, r);
}

int modify(int o, int l, int r) {
    int oo = ++node_cnt;
    lc[oo] = lc[o];
    rc[oo] = rc[o];
    sum[oo] = sum[o] + 1;
    if(l == r)
        return oo;
    int mid = (l + r) >> 1;
    if(p <= mid) lc[oo] = modify(lc[oo], l, mid);
    else rc[oo] = modify(rc[oo], mid + 1, r);
    return oo;
}

int query(int u, int v, int l, int r, int k) {
    int ans, mid = ((l + r) >> 1), x = sum[lc[v]] - sum[lc[u]];
    if(l == r)
        return l;
    if(x >= k) ans = query(lc[u], lc[v], l, mid, k);
    else ans = query(rc[u], rc[v], mid + 1, r, k - x);
    return ans;
}

int main() {
    int l, r, k, q, ans;
    scanf("%d%d", &n, &m);
    for(register int i = 1; i <= n; i += 1)
        scanf("%d", &a[i]), b[i] = a[i];
    sort(b + 1, b + n + 1);
    q = unique(b + 1, b + n + 1) - b - 1;
    build(rt[0], 1, q);
    for(register int i = 1; i <= n; i += 1) {
        p = lower_bound(b + 1, b + q + 1, a[i]) - b;//可以视为查找最小下标的匹配值，核心算法是二分查找
        rt[i] = modify(rt[i - 1], 1, q);
    }
    while(m--) {
        scanf("%d%d%d", &l, &r, &k);
        ans = query(rt[l - 1], rt[r], 1, q, k);
        printf("%d\n", b[ans]);
    }
    return 0;
}