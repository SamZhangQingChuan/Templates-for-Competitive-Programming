using fft::N;

namespace Poly {
    int tmp1[N], tmp2[N], tmp3[N], mod = ;
    int iv[N];
    
    void init () {
        iv[1] = 1;
        for (int i = 2; i < N; ++i) {
            iv[i] = (mod - (ll) mod / i * iv[mod % i] % mod);
        }
    }
    
    // res = 1 / poly
    void inv (int poly[], int res[], int n) {
        int deg = n - 1;
        std::vector<int> degs;
        while (deg > 0) {
            degs.push_back (deg);
            deg >>= 1;
        }
        std::reverse (degs.begin (), degs.end ());
        res[0] = inverse (poly[0], mod);
        deg = 1;
        for (int t: degs) {
            fft::conv (poly, res, t + 1, deg, mod, tmp1);
            fft::conv (res, tmp1 + deg, t + 1 - deg, t + 1 - deg, mod, tmp1);
            for (int i = 0; i < t + 1 - deg; ++i) {
                res[i + deg] = mod - tmp1[i];
            }
            deg = t + 1;
        }
    }
    
    // res = ln(poly), poly[0] should be 1
    void log (int poly[], int res[], int n) {
        assert(poly[0] == 1);
        inv (poly, tmp2, n);
        for (int i = 0; i < n - 1; ++i) {
            res[i] = (ll) poly[i + 1] * (i + 1) % mod;
        }
        fft::conv (res, tmp2, n - 1, n, mod, res);
        for (int i = n - 1; i >= 1; --i) {
            res[i] = (ll) res[i - 1] * iv[i] % mod;
        }
        res[0] = 0;
    }
    
    // res = exp(poly), poly[0] should be 0
    void exp (int poly[], int res[], int n) {
        assert(poly[0] == 0);
        while (n & n - 1)n += lowbit(n);
        if (n == 1) {
            res[0] = 1;
            return;
        }
        exp (poly, res, n>>1);
        log (res, tmp3, n);
        for (int i = 0; i < n; ++i) {
            tmp3[i] = poly[i] - tmp3[i];
            if (tmp3[i] < 0) tmp3[i] += mod;
        }
        if (++tmp3[0] == mod) tmp3[0] = 0;
        fft::conv (tmp3, res, n, n, mod, res);
        memset (res + n, 0, sizeof (*res) * n);
    }
}

// polynomial arithmetic in O(n^2)
// mod should be a prime greater than n
namespace poly_brutal {
    // f = f * g mod x^n
    void conv (int n, ll f[], ll g[], ll mod) {
        for (int i = n - 1; i >= 0; --i) {
            ll tmp = 0;
            for (int j = 0; j <= i; ++j) {
                tmp += f[j] * g[i - j] % mod;
            }
            f[i] = tmp % mod;
        }
    }
    
    // f = g^{-1} mod x^n, g[0] != 0
    void inv (int n, ll f[], ll g[], ll mod) {
        assert(g[0] != 0);
        ll inv0 = inverse (g[0], mod);
        for (int i = 0; i < n; ++i) {
            ll tmp = 0;
            for (int j = 0; j < i; ++j) {
                tmp += f[j] * g[i - j] % mod;
            }
            if (!i) f[i] = inv0;
            else f[i] = (mod - tmp % mod) * inv0 % mod;
        }
    }
    
    // f = ln(g) mod x^n, g[0] = 1
    void log (int n, ll f[], ll g[], ll mod) {
        assert(g[0] == 1);
        inv (n, f, g, mod);
        for (int i = n - 1; i >= 0; --i) {
            ll tmp = 0;
            for (int j = 0; j <= i; ++j) {
                tmp += f[i - j] * (j == n ? 0 : g[j + 1]) % mod * (j + 1) % mod;
            }
            f[i] = tmp % mod;
        }
        for (int i = n - 1; i >= 1; --i) {
            f[i] = f[i - 1] * inverse (i, mod) % mod;
        }
        f[0] = 0;
    }
    
    // f= exp(g) mod x^n, g[0] = 0
    void exp (int n, ll f[], ll g[], ll mod) {
        assert(g[0] == 0);
        f[0] = 1;
        for (int i = 1; i < n; ++i) {
            ll tmp = 0;
            for (int j = 1; j <= i; ++j) {
                tmp += j * g[j] % mod * f[i - j] % mod;
            }
            f[i] = tmp % mod * inverse (i, mod) % mod;
        }
    }
}