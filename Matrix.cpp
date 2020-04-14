struct matrix {
    //add mod at last if there is negative number
    vector <VLL> v;
    int x, y;
    
    matrix(int n = 0, int m = 0, int value = 0) : x(n), y(m) {
        v = vector<VLL>(n, VLL(m, 0));
        if(value == 1) {
            REP(i, 0, n)
            {
                v[i][i] = 1;
            }
        }
    }
    
    matrix operator*(const matrix &o) const {
        matrix ans(x, o.y);
        REP(i, 0, x)
        {
            REP(k, 0, y)
            {
                REP(j, 0, o.y)
                {
                    ans.v[i][j] = (ans.v[i][j] + v[i][k] * o.v[k][j]) % mod;
                }
            }
        }
        return ans;
    }
    
    
    matrix operator+(const matrix &o) const {
        assert(x == o.x && y == o.y);
        matrix ans = *this;
        REP(i, 0, x)
        {
            REP(j, 0, y)
            {
                ans.v[i][j] += o.v[i][j];
                ans.v[i][j] %= mod;
            }
        }
        return ans;
    }
    
    
    friend matrix fast(matrix a, ll b) {
        matrix ans(a.x, a.y, 1);
        assert(a.x == a.y);
        while(b) {
            if(b & 1) {
                b--;
                ans = ans * a;
            } else {
                b /= 2;
                a = a * a;
            }
        }
        return ans;
    }
    
    void print() {
        printf("row = %d, column = %d\n", x, y);
        REP(i, 0, x)
        {
            REP(j, 0, y)
            {
                cout << v[i][j] << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }
    
};

