using fft::N;


// call init before use
namespace Poly {
    int tmp1[N], tmp2[N], tmp3[N], mod = 998244353;
    int iv[N];
    
    void init () {
        iv[1] = 1;
        for (int i = 2; i < N; ++i) {
            iv[i] = (mod - (ll) mod / i * iv[mod % i] % mod);
        }
    }
    
    void prepare (int poly[], int n) {
        for (int i = 0; i < n; i++)poly[i] = MOD (poly[i], mod);
    }
    
    // res = 1 / poly
    void inv (int poly[], int res[], int n) {
        prepare (poly, n);
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
        prepare (poly, n);
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
        prepare (poly, n);
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
    
    // res = sqrt(poly), poly[0] should be 1
    void sqrt (int poly[], int res[], int n) {
        prepare (poly, n);
        assert(poly[0] == 1);
        while (n & (n - 1)) n += n & (-n);
        if (n == 1) {
            res[0] = 1;
            return;
        }
        sqrt (poly, res, n>>1);
        fill (tmp2 + n / 2, tmp2 + n, 0);
        fill (res + n / 2, res + n, 0);
        inv (res, tmp2, n);
        
        fft::conv (poly, tmp2, n, n, mod, tmp1);
        for (int i = 0; i < n; i++) {
            res[i] = (ll) iv[2] * ((res[i] + tmp1[i]) % mod) % mod;
        }
    }
}
