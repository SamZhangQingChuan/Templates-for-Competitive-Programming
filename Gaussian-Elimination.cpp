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

int det_mod(int n, int mod, vector <vector<int>> mat) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            mat[i][j] %= mod;
        }
    }
    ll ret = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j)
            for (; mat[j][i]; ret = -ret) {
                ll t = mat[i][i] / mat[j][i];
                for (int k = i; k < n; ++k) {
                    mat[i][k] = (mat[i][k] - mat[j][k] * t) % mod;
                    std::swap(mat[j][k], mat[i][k]);
                }
            }
        if (mat[i][i] == 0) return 0;
        ret = ret * mat[i][i] % mod;
    }
    if (ret < 0) ret += mod;
    return (int) ret;
}
