#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

#define PB push_back
#define PF push_front
#define LB lower_bound
#define UB upper_bound
#define fr(x) freopen(x,"r",stdin)
#define fw(x) freopen(x,"w",stdout)
#define REP(i, from, to) for(ll i = from;i<to;i++)
#define RREP(i, from, to) for(ll i = from;i>=to;i--)
#define complete_unique(a) a.erase(unique(begin(a),end(a)),end(a))
#define mst(x, a) memset(x,a,sizeof(x))
#define all(a) begin(a),end(a)
#define rall(a) rbegin(a),rend(a)
#define MP make_pair
#define lowbit(x) ((x)&(-(x)))
#define bitcnt(x) (__builtin_popcountll(x))
#define lson (ind<<1)
#define rson (ind<<1|1)
#define se second
#define fi first
#define EX0 exit(0);

using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using VLL = std::vector<ll>;
using VI = std::vector<int>;
using PII = std::pair<int, int>;
using PLL = std::pair<ll, ll>;

using namespace __gnu_pbds; //required
using namespace std;
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
const ll mod = 1e9 + 7;


string to_string(string s) { return '"' + s + '"'; }

string to_string(const char *s) { return to_string((string) s); }

string to_string(bool b) { return (b ? "true" : "false"); }

template<typename A, typename B>
string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }

template<typename A>
string to_string(A v) {
    bool first = true;
    string res = "{";
    for(const auto &x: v) {
        if(!first) { res += ", "; }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

void debug_out() { cerr << endl; }

template<typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}

#ifdef LOCAL
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define dbg(...) do {} while(0)
#endif

template<typename T, typename S>
inline bool upmin(T &a, const S &b) { return a > b ? a = b, 1 : 0; }

template<typename T, typename S>
inline bool upmax(T &a, const S &b) { return a < b ? a = b, 1 : 0; }


ull twop(ll x) { return 1ULL << x; }

ll MOD(ll a, ll m) {
    a %= m;
    if(a < 0)a += m;
    return a;
}

ll inverse(ll a, ll m) {
    a = MOD(a, m);
    if(a <= 1)return a;
    return MOD((1 - inverse(m, a) * m) / a, m);
}

template<typename T>
T sqr(T x) { return x * x; }

template<typename T>
ll sz(const T &x) { return x.size(); }

ll fast(ll a, ll b, ll mod) {
    a %= mod;
    if(b < 0)a = inverse(a, mod), b = -b;
    ll ans = 1;
    while(b) {
        if(b & 1)ans = ans * a % mod;
        a = a * a % mod;
        b /= 2;
    }
    return ans % mod;
}


namespace SOLVE {
    void main() {
    
    }
}

#ifdef __APPLE__
#define INPUT_FILE "/Users/qingczha/ClionProjects/Playground/input.txt"
#define OUTPUT_FILE "/Users/qingczha/ClionProjects/Playground/output.txt"
#else
#define INPUT_FILE "C:/Users/qingczha/CLionProjects/playground/input.txt"
#define OUTPUT_FILE "C:/Users/qingczha/CLionProjects/playground/output.txt"
#endif

signed main() {
#ifdef LOCAL
    fr(INPUT_FILE);
    fw(OUTPUT_FILE);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int t = 1;
//    cin >> t;
    for(int i = 1; i <= t; i++) {
//        cout<<"Case #"<<i<<": ";
        SOLVE::main();
        
    }








//    clock_t st = clock();
//    while(clock() - st < 3.0 * CLOCKS_PER_SEC){
//
//    }
    
    
    
    
    
    
    return 0;
}
