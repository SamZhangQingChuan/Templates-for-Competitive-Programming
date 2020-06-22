namespace NTT {
    const int mod = 998244353, g = 3;
    
    void bit_reverse_swap (VI &a) {
        int n = sz(a);
        for (int i = 1, j = n>>1, k; i < n - 1; i++) {
            if (i < j) swap (a[i], a[j]);
            for (k = n>>1; j >= k; j -= k, k >>= 1);
            j += k;
        }
    }
    
    void NTT (VI &a, int type) {
        bit_reverse_swap (a);
        int n = sz (a);
        for (int i = 2; i <= n; i *= 2) {
            const auto wi = fast (g, type * (mod - 1) / i, mod); // fp(g, (mod - 1) / i) 是 i 次单位根
            for (int j = 0; j < n; j += i) {
                ll w = 1;
                for (int k = j, h = i / 2; k < j + h; k++) {
                    int t = w * a[k + h] % mod, u = a[k];
                    a[k] = (u + t) % mod;
                    a[k + h] = (u - t + mod) % mod;
                    w = w * wi % mod;
                }
            }
        }
        const ll inv = inverse (n, mod);
        if (type == -1) for (auto &x : a) x = x * inv % mod;
    }
    
    
    VI conv (const VI &a, const VI &b, const int n, const int m, const int mod = NTT::mod) {
        VI _a (begin (a), begin (a) + n);
        VI _b (begin (b), begin (b) + m);
        int len = 1;
        while (len <= n + m - 2) len <<= 1;
        while (len != lowbit(len)) len += lowbit(len);
        _a.resize (len), _b.resize (len);
        NTT (_a, 1), NTT (_b, 1);
        REP(i, 0, len) _a[i] = (ll) _a[i] * _b[i] % mod;
        NTT (_a, -1);
        _a.resize (n + m - 1);
        return _a;
    }
}


namespace Poly {
    using NTT::mod;
    using NTT::conv;
    VI iv ({0, 1});
    
    void init (const int n) {
        while (sz(iv) < n) {
            iv.emplace_back ((mod - (ll) mod / sz(iv) * iv[mod % sz(iv)] % mod));
        }
    }
    
    //B(x) ≡ 2C(x) − A(x)C(x)^2
    VI inv (const VI &poly) {
        int n = 1;
        VI res (1);
        res[0] = inverse (poly[0], mod);
        while (n < sz(poly)) {
            auto new_res = conv (res, res, n, n, mod);
            new_res = conv (poly, new_res, min (2 * n, sz(poly)), sz(new_res), mod);
            res.resize (2 * n, 0);
            REP(i, 0, 2 * n) {
                res[i] = (2ll * res[i] - (i < sz(new_res) ? new_res[i] : 0) + mod) % mod;
            }
            n *= 2;
        }
        res.resize (sz(poly));
        return res;
    }
    
    VI integrate (const VI &poly) {
        init (sz(poly));
        VI res (sz(poly), 0);
        REP(i, 1, sz (res)) {
            res[i] = poly[i - 1] * (ll) iv[i] % mod;
        }
        return res;
    }
    
    VI differentiate (const VI &poly) {
        VI res (sz(poly), 0);
        REP(i, 0, sz (res) - 1) {
            res[i] = poly[i + 1] * ll (i + 1) % mod;
        }
        return res;
    }
    
    VI log (const VI &poly) {
        auto res = integrate (conv (differentiate (poly), inv (poly), sz(poly), sz(poly), mod));
        res.resize (sz(poly));
        return res;
    }
    
    // g ≡ (1 − ln(g0) + f)g0
    VI exp (const VI &poly) {
        int n = 1;
        VI res (1, 1);
        VI tmp;
        while (n < sz(poly)) {
            tmp = res;
            tmp.resize (2 * n, 0);
            tmp = log (tmp);
            REP(i, 0, 2 * n) {
                tmp[i] = (ll (i == 0) - tmp[i] + (i < sz(poly) ? poly[i] : 0) + mod) % mod;
            }
            res = conv (res, tmp, n, 2 * n, mod);
            res.resize (2 * n, 0);
            n *= 2;
        }
        res.resize (sz(poly));
        return res;
    }
    
    // k < mod
    VI power (const VI &poly, const ll k) {
        auto low = find_if (all(poly), [] (const int x) { return x != 0; });
        if (low == end (poly))return VI (sz(poly), 0);
        ll padding = (low - begin (poly)) * k;
        if (padding >= sz(poly))return VI (sz(poly), 0);
        VI tmp (low, end (poly));
        ll inv = inverse (*low, mod);
        for (auto &x:tmp) x = x * inv % mod;
        tmp = log (tmp);
        for (auto &x:tmp) x = x * k % mod;
        tmp = exp (tmp);
        ll pw = fast (inv, -k, mod);
        for (auto &x:tmp) x = x * pw % mod;
        if (padding) {
            VI zeros (padding, 0);
            tmp.insert (tmp.begin (), all(zeros));
        }
        tmp.resize (sz(poly), 0);
        return tmp;
    }
    
    // TODO: sqrt
    
    
    // TODO: div and mod
    
    
    // TODO: Multi Point Eval
}
