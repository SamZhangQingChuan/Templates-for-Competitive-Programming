struct PrimeCounting {
private:
    void EratosthenesSieve (const int n, VLL &primes) {
        vector<ll> numbers (n + 1);
        for (ll i = 2; i <= n; i++) {
            if (!numbers[i]) {
                primes.PB (i);
                for (ll j = i * i; j <= n; j += i)numbers[j] = 1;
            }
        }
    }
    
    void compute () {
        for (auto p:primes) {
            for (int i = 0; i < sz(quotient); i++) {
                if (p * p > quotient[i])break;
                // 卡常时如不需要 mod 可以去掉
                sum[i] = MOD (sum[i] - (sum[get_id (divisor[i] * p)] - sum[get_id ((n / (p - 1)))]), mod);
            }
        }
    }
    
    inline int get_id (const ll &divisor) {
        if (n / divisor <= lim) {
            return id[0][n / divisor];
        } else {
            return id[1][divisor];
        }
    }

public:
    VI id[2];
    VLL quotient, sum, divisor, primes;
    const ll lim, n, mod;
    
    // 传入积性函数前缀和函数 prefix_f
    // 答案在 sum[0]
    template<typename T>
    PrimeCounting (const ll n, T prefix_f, const ll mod):n (n), lim (sqrt (n)), mod (mod) {
        id[0] = id[1] = VI (lim + 1, 0);
        for (ll i = 1; i <= n; i = n / (n / i) + 1) {
            quotient.emplace_back (n / i);
            divisor.emplace_back (i);
            sum.emplace_back (prefix_f (n / i));
            if (n / i <= lim) {
                id[0][n / i] = sz(quotient) - 1;
            } else {
                id[1][i] = sz(quotient) - 1;
            }
        }
        EratosthenesSieve (lim, primes);
        compute ();
    }
    
};
