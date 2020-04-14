const ll maxn =;
ll fac[maxn], facinv[maxn], inv[maxn];

void init() {
    fac[0] = 1;
    REP(i, 1, maxn)
    fac[i] = i * (fac[i - 1]) % mod;
    facinv[maxn - 1] = inverse(fac[maxn - 1], mod);
    RREP(i, maxn - 2, 0)
    {
        facinv[i] = facinv[i + 1] * (i + 1) % mod;
    }
    inv[1] = 1;
    for (int i = 2; i < maxn; i++)
        inv[i] = (mod - (ll) mod / i * inv[mod % i] % mod);
}

ll combi(int n, int m) {
    if (n < 0 || m < 0 || n < m)return 0;
    return fac[n] * facinv[m] % mod * facinv[n - m] % mod;
}

