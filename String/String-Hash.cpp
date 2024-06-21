// 1-based
// 支持char/int/ll
// push      - 加在末尾
// build     - 重建
// hash(l,r) - 获取 [l,r] 的 hash
struct Hashing {
    array<ll, 2> seed, mod;
    array<vector<ll>, 2> hs, pw;
    
    Hashing (array<ll, 2> seed = {28, 31},
             array<ll, 2> mod = {1000000007, 1000173169}) : seed (seed), mod (mod) {
        init ();
    }
    
    void init () {
        hs[0] = hs[1] = {0};
        pw[0] = pw[1] = {1};
    }
    
    void push (ll ch) {
        assert (ch != 0);
        for (int i = 0; i < 2; i++) {
            pw[i].push_back (pw[i].back () * seed[i] % mod[i]);
            hs[i].push_back ((hs[i].back () * seed[i] + ch) % mod[i]);
        }
    }
    
    void pop () {
        assert (size () > 1);
        for (int i = 0; i < 2; i++) {
            pw[i].pop_back ();
            hs[i].pop_back ();
        }
    }
    
    
    template<typename T>
    void build (T begin, T end) {
        init ();
        while (begin != end) {
            push (*(begin++));
        }
    }
    
    template<typename T>
    void push (T begin, T end) {
        while (begin != end) {
            push (*(begin++));
        }
    }
    
    ll hash (int l, int r) {
        l--;
        assert (l <= r and r <= size ());
        array<ll, 2> ans{0, 0};
        if (l >= r)return (ans[0]<<32) + ans[1];
        for (int i = 0; i < 2; i++) {
            ans[i] = (hs[i][r] - hs[i][l] * pw[i][r - l]) % mod[i];
            if (ans[i] < 0)ans[i] += mod[i];
        }
        return (ans[0]<<32) + ans[1];
    }
    
    int size () {
        return hs[0].size () - 1;
    }
};
