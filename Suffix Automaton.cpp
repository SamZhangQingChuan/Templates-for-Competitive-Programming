struct SAM {
    static const int maxn = 300010 * 2;
    struct node {
        node *nxt[26], *fail;
        int cnt;
        int len;
    };
    
    node *root;
    int cnt;
    node no[maxn];
    
    node *newnode() {
        return &no[cnt++];
    }
    
    SAM() {
        cnt = 0;
        root = newnode();
    }
    
    void add(const string &s) {
        node *cur = root;
        REP(i, 0, sz(s)) {
            cur = add(cur, s[i] - 'a');
        }
    }
    
    node *add(node *p, int c) {
        node *cur = newnode();
        cur->len = p->len + 1;
        while(p && !p->nxt[c])p->nxt[c] = cur, p = p->fail;
        if(!p) {
            cur->fail = root;
            return cur;
        }
        node *q = p->nxt[c];
        if(q->len == p->len + 1) {
            cur->fail = q;
        } else {
            node *nq = newnode();
            *nq = *q;
            nq->len = p->len + 1;
            q->fail = cur->fail = nq;
            while(p && p->nxt[c] == q)p->nxt[c] = nq, p = p->fail;
        }
        return cur;
    }
    
    void pre(const string &s) {
        node *cur = root;
        REP(i, 0, sz(s)) {
            cur = cur->nxt[s[i] - 'a'];
            cur->cnt++;
        }
    }
    
    //call pre first
    //return sum of cnt
    void getCnt() {
        vector<node *> v;
        REP(i, 1, cnt) {
            v.PB(&no[i]);
        }
        sort(all(v), [](const node *a, const node *b) {
            return a->len > b->len;
        });
        REP(i, 0, sz(v)) {
            v[i]->fail->cnt += v[i]->cnt;
        }
    }
    
    ll getNumOfDistinctSubstrings() {
        auto ans = 0;
        REP(i, 1, cnt)ans += no[i].len - no[i].fail->len;
        return (ans);
    }
};
