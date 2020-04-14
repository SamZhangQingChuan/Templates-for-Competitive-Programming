//1-based
struct Hashing {
    ull seed, Mod;
    vector <ull> hs, pw;
    
    Hashing(ull seed = 31, ull Mod = 1000173169) : seed(seed), Mod(Mod) {}
    
    void build(int n, const char* s) {
        hs.assign(n + 1, 0);
        pw.assign(n + 1, 1);
        pw[0] = 1;
        for (int i = 1; i <= n; ++i) pw[i] = pw[i - 1] * seed % Mod;
        for (int i = 1; i <= n; ++i) hs[i] = (hs[i - 1] * seed + s[i]) % Mod;
    }
    
    ull hash(int l, int r) { return (hs[r] - hs[l - 1] * pw[r - l + 1] % Mod + Mod) % Mod; }
};

