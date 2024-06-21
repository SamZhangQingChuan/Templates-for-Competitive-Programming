struct dictOfBasicFactors {
    //设置maxn = 2*maxLen
    //设置n
    //设置s[i],0-based
    static const int maxn = 400010, bit = 20;
    PII id[maxn][bit];
    pair<PII, int> tmp[maxn];
    int rk[maxn], n, s[maxn];
    int maxp[maxn];
    
    void build() {
        REP(i, 1, maxn)
        {
            if (i == lowbit(i))maxp[i] = log2(i);
            else maxp[i] = maxp[i - lowbit(i)];
        }
        mst(rk, -1);
        REP(i, 0, n)
        rk[i] = s[i], id[i][0] = MP(rk[i], 0);
        REP(i, 1, bit)
        {
            REP(j, 0, n)
            tmp[j] = MP(MP(rk[j], rk[j + twop(i - 1)]), j), id[j][i] = tmp[j].fi;
            sort(tmp, tmp + n);
            rk[tmp[0].se] = 1;
            REP(j, 1, n)
            rk[tmp[j].se] = rk[tmp[j - 1].se] + ((tmp[j].fi == tmp[j - 1].fi) ? 0 : 1);
        }
    }
    
    bool equal(int a, int b, int len) {
        return bequal(a, b, maxp[len]) && bequal(a + len - twop(maxp[len]), b + len - twop(maxp[len]), maxp[len]);
    }
    
    bool bequal(int a, int b, int bit) {
        return id[a][bit] == id[b][bit];
    }
    
    int lcp(int a, int b) {
        if (a == b)return n - a;
        int l = 0, r = n;
        while (l < r) {
            int mid = (l + r) / 2 + 1;
            if (equal(a, b, mid))l = mid;
            else r = mid - 1;
        }
        return l;
    }
    
    bool cmp(int a, int b) {
        return rk[a] < rk[b];
    }
};
