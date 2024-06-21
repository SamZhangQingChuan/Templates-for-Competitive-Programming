template<typename T>
class SuffixArray {
public:
    void build_SA (const T &str, vector<int> &sa, vector<int> &rk) {
        
        const int len = sz(str);
        vector<pair<PII, int>> ord[2] = {vector<pair<PII, int >> (len), vector<pair<PII, int >> (len)};
        sa = std::vector<int> (len);
        rk = std::vector<int> (len);
        REP(i, 0, len) {
            ord[1][i] = MP (MP (str[i], 0), i);
        }
        for (int b = 0;; b++) {
            int cur = b % 2;
            sort (all(ord[cur ^ 1]));
            REP(i, 0, len) {
                rk[ord[cur ^ 1][i].se] =
                        i == 0 ? 0 : (rk[ord[cur ^ 1][i - 1].se] + (ord[cur ^ 1][i - 1].fi != ord[cur ^ 1][i].fi));
            }
            if (rk[ord[cur ^ 1][len - 1].se] == len - 1)break;
            REP(i, 0, len)ord[cur][i] = MP (MP (rk[i], (i + twop (b) < len) ? rk[i + twop (b)] : -1e9), i);
        }
        REP(i, 0, len)sa[rk[i]] = i;
    }
    
    vector<vector<int>> st;
    
    void build_height (const T &str, const vector<int> &sa, const vector<int> &rk, vector<int> &height) {
        height = std::vector<int> (sz(str), 0);
        const int len = sz(str);
        REP(i, 0, len) {
            if (rk[i] == 0)continue;
            while (i + height[rk[i]] < len && sa[rk[i] - 1] + height[rk[i]] < len &&
                   str[i + height[rk[i]]] == str[sa[rk[i] - 1] + height[rk[i]]]) {
                height[rk[i]]++;
            }
            if (i != len - 1) {
                height[rk[i + 1]] = max (0, height[rk[i]] - 1);
            }
        }
    }
    
    T str;
    vector<int> sa, rk;
    
    void init (const T &s, bool getHeight = 0) {
        str = s;
        build_SA (str, sa, rk);
        if (getHeight) {
            st = vector<vector<int >> (ceil (log2 (sz(s)) + 1e-2), vector<int> (sz(s)));
            build_height (str, sa, rk, st[0]);
            REP(i, 0, sz (st) - 1) {
                REP(j, 0, sz (s) - twop (i)) {
                    st[i + 1][j] = min (st[i][j], st[i][j + twop (i)]);
                }
            }
        }
    }
    
    void test () {
        REP(i, 0, sz (str)) {
            cout<<(i)<<" ";
            REP(j, sa[i], sz (str)) {
                if (str[j] < 0)break;
                cout<<char (str[j]);
            }
            cout<<endl;
        }
    }
    
    int getLCP (int l, int r) {
        if (l == r) {
            return sz(str) - l;
        } else {
            l = rk[l], r = rk[r];
            if (l > r)swap (l, r);
            l++;
            int lvl = floor (log2 (r - l + 1));
            return min (st[lvl][l], st[lvl][r - twop (lvl) + 1]);
        }
    }
    
};
