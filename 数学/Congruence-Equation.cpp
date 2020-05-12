ll mul(ll a, ll b, ll mod) {
    a %= mod;
    b %= mod;
    if (a < mod)a += mod;
    if (b < mod)b += mod;
    ll res = 0;
    while (b > 0) {
        if (b & 1) res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

//返回值为 gcd 以及 a,b 的系数
pair <ll, PLL> exgcd(ll a, ll b) {
    valarray <ll> equation[2] = {{a, 1, 0},
                                 {b, 0, 1}};
    while (equation[1][0]) {
        ll q = equation[0][0] / equation[1][0];
        equation[0] -= q * equation[1];
        swap(equation[0], equation[1]);
    }
    return MP(equation[0][0], MP(equation[0][1], equation[0][2]));
}

// x = a.fi mod a.se
// x = b.fi mod b.se
// returns x = res.fi mod res.se
// (-1,-1) => solution doesn't exist
PLL crt(PLL a, PLL b) {
    PLL res;
    res.se = a.se / gcd(a.se, b.se) * b.se;
    pair <ll, PLL> equation = exgcd(a.se, b.se);
    ll q = (b.fi - a.fi) / equation.fi % res.se;
    if (q < 0)q += res.se;
    res.fi = mul(mul(q, equation.se.fi, res.se), a.se, res.se) + a.fi;
    if (res.fi % a.se != a.fi)return MP(-1, -1);
    if (res.fi % b.se != b.fi)return MP(-1, -1);
    return res;
}
