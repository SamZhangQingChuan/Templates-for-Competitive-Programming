void EratosthenesSieve(const int n, vector <ll> &primes) {
    vector <ll> numbers(n + 1);
    for (ll i = 2; i <= n; i++) {
        if (!numbers[i]) {
            primes.PB(i);
            for (ll j = i * i; j <= n; j += i)numbers[j] = 1;
        }
    }
}


void EulerSieve(const ll n, vector <ll> &primes, vector <ll> &phi, vector <ll> &mu) {
    phi = vector<ll>(n + 1);
    phi[1] = 1;
    mu = vector<ll>(n + 1);
    mu[1] = 1;
    vector <ll> isPrime(n + 1, 1);
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.PB(i);
            phi[i] = i - 1;
            mu[i] = -1;
        }
        for (const auto &j: primes) {
            ll num = 1LL * j * i;
            if (num > n)break;
            isPrime[num] = 0;
            if (i % j == 0) {
                phi[num] = phi[i] * j;
                mu[num] = 0;
                break;
            } else {
                phi[num] = phi[i] * (j - 1);
                mu[num] = -mu[i];
            }
        }
    }
}
