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

