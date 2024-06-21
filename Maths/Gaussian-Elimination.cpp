typedef double flt;
const int MAXN = 64;
const flt eps = 1e-8;

bool gauss(flt a[][MAXN], flt b[], int n) {
    for (int k = 0, i, j, s; k < n; ++k) {
        for (s = k, i = k + 1; i < n; ++i)
            if (fabs(a[i][k]) > fabs(a[s][k]))s = i;
        if (fabs(a[s][k]) < eps)return false;
        if (s != k) {
            std::swap(b[s], b[k]);
            for (i = k; i < n; ++i) std::swap(a[s][i], a[k][i]);
        }
        for (j = k + 1; j < n; ++j) {
            flt t = -a[j][k] / a[k][k];
            b[j] += b[k] * t;
            for (i = k + 1; i < n; ++i)a[j][i] += t * a[k][i];
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        b[i] /= a[i][i];
        for (int j = 0; j < i; ++j)b[j] -= a[j][i] * b[i];
    }
    return 1;
}


// mod 可为合数
int det_mod (const int n, const int mod, vector<vector<int>> mat) {
    assert(mod > 0);
    assert(sz (mat) == n and sz (mat[0]) == n);
    for (auto &row:mat)
        for (auto &elem:row)
            elem = MOD (elem, mod);
    ll ret = 1;
    for (int col = 0; col < n; col++) {
        for (int row = col + 1; row < n; row++) {
            if (mat[row][col]) {
                int co = inverse (mat[row][col] / gcd (mat[row][col], mod), mod);
                if (co != 1) {
                    for (auto &v:mat[row]) {
                        v = (ll) v * co % mod;
                    }
                    ret = ret * inverse (co, mod) % mod;
                }
                while (mat[row][col] != 0) {
                    ll t = mat[col][col] / mat[row][col];
                    if (t)
                        for (int k = col; k < n; ++k) {
                            mat[col][k] = MOD (mat[col][k] - mat[row][k] * t, mod);
                        }
                    swap (mat[col], mat[row]);
                    ret *= -1;
                }
            }
        }
        ret *= mat[col][col];
        ret %= mod;
    }
    return MOD (ret, mod);
}
