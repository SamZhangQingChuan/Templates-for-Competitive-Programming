#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
//#pragma GCC optimize(3)
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
//#pragma GCC target("sse3","sse2","sse")
//#pragma GCC target("avx","sse4","sse4.1","sse4.2","ssse3")
//#pragma GCC target("f16c")
//#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")
//#pragma GCC diagnostic error "-fwhole-program"
//#pragma GCC diagnostic error "-fcse-skip-blocks"
//#pragma GCC diagnostic error "-funsafe-loop-optimizations"
//#pragma GCC diagnostic error "-std=c++14"
#include "bits/stdc++.h"
#include "ext/pb_ds/tree_policy.hpp"
#include "ext/pb_ds/assoc_container.hpp"

#define PB push_back
#define PF push_front
#define LB lower_bound
#define UB upper_bound
#define fr(x) freopen(x,"r",stdin)
#define fw(x) freopen(x,"w",stdout)
#define REP(x, l, u) for(ll x = l;x<u;x++)
#define RREP(x, l, u) for(ll x = l;x>=u;x--)
#define complete_unique(a) a.erase(unique(begin(a),end(a)),end(a))
#define mst(x, a) memset(x,a,sizeof(x))
#define all(a) begin(a),end(a)
#define rall(a) rbegin(a),rend(a)
#define PII pair<int,int>
#define PLL pair<ll,ll>
#define MP make_pair
#define lowbit(x) ((x)&(-(x)))
#define bitcnt(x) (__builtin_popcountll(x))
#define lson (ind<<1)
#define rson (ind<<1|1)
#define se second
#define fi first
#define sz(x) ((int)x.size())
#define EX0 exit(0);

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;
using namespace __gnu_pbds; //required
using namespace std;
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
typedef vector<ll> VLL;
typedef vector<int> VI;
const ll mod = 1e9 + 7;


string to_string (string s) { return '"' + s + '"'; }

string to_string (const char *s) { return to_string ((string) s); }

string to_string (bool b) { return (b ? "true" : "false"); }

template<typename A, typename B>
string to_string (pair<A, B> p) { return "(" + to_string (p.first) + ", " + to_string (p.second) + ")"; }

template<typename A>
string to_string (A v) {
    bool first = true;
    string res = "{";
    for (const auto &x : v) {
        if (!first) { res += ", "; }
        first = false;
        res += to_string (x);
    }
    res += "}";
    return res;
}

void debug_out () { cerr<<endl; }

template<typename Head, typename... Tail>
void debug_out (Head H, Tail... T) {
    cerr<<" "<<to_string (H);
    debug_out (T...);
}

#ifdef LOCAL
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define dbg(...) {}
#endif

template<typename T, typename S>
inline bool upmin (T &a, const S &b) { return a > b ? a = b, 1 : 0; }

template<typename T, typename S>
inline bool upmax (T &a, const S &b) { return a < b ? a = b, 1 : 0; }


ull twop (ll x) { return 1ULL<<x; }

ll MOD (ll a, ll m) {
    a %= m;
    if (a < 0)a += m;
    return a;
}

ll inverse (ll a, ll m) {
    a = MOD (a, m);
    if (a <= 1)return a;
    return MOD ((1 - inverse (m, a) * m) / a, m);
}

template<typename T>
T sqr (T x) { return x * x; }

ll gcd (ll a, ll b) {
    a = abs (a), b = abs (b);
    while (b != 0) {
        a %= b;
        swap (a, b);
    }
    return a;
}

ll fast (ll a, ll b, ll mod) {
    a %= mod;
    if (b < 0)a = inverse (a, mod), b = -b;
    ll ans = 1;
    while (b) {
        if (b & 1)ans = ans * a % mod;
        a = a * a % mod;
        b /= 2;
    }
    return ans % mod;
}


namespace SOLVE {
    void main () {
    
    }
}


signed main () {
#ifdef LOCAL
    fr("/Users/zhangqingchuan/Desktop/cp/cp/input.txt");
    fw("/Users/zhangqingchuan/Desktop/cp/cp/output.txt");
#endif
    ios::sync_with_stdio (false);
    cin.tie (nullptr);
    cout.tie (nullptr);
    
    
    int t = 1;
//    cin >> t;
    for (int i = 1; i <= t; i++) {
//        cout<<"Case #"<<i<<": ";
        SOLVE::main ();
        
    }








//    clock_t st = clock();
//    while(clock() - st < 3.0 * CLOCKS_PER_SEC){
//
//    }
    
    
    
    
    
    
    return 0;
}
