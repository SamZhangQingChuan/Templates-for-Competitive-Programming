struct SAM {
    static const int maxn = 300010 * 2;
    struct Node {
        Node *nxt[26], *fail;
        int cnt;
        int len;
    };
    
    Node *root;
    int cnt;
    Node no[maxn];
    
    Node *newNode () {
        memset (&no[cnt], 0, sizeof (Node));
        return &no[cnt++];
    }
    
    void init () {
        cnt = 0;
        root = newNode ();
    }
    
    SAM () {
        init ();
    }
    
    void add (const string &s) {
        Node *cur = root;
        REP(i, 0, sz (s)) {
            cur = add (cur, s[i] - 'a');
        }
    }
    
    Node *add (Node *p, int c) {
        Node *cur = newNode ();
        cur->len = p->len + 1;
        while (p && !p->nxt[c])p->nxt[c] = cur, p = p->fail;
        if (!p) {
            cur->fail = root;
            return cur;
        }
        Node *q = p->nxt[c];
        if (q->len == p->len + 1) {
            cur->fail = q;
        } else {
            Node *nq = newNode ();
            *nq = *q;
            nq->len = p->len + 1;
            q->fail = cur->fail = nq;
            while (p && p->nxt[c] == q)p->nxt[c] = nq, p = p->fail;
        }
        return cur;
    }
    
    void pre (const string &s) {
        Node *cur = root;
        REP(i, 0, sz (s)) {
            cur = cur->nxt[s[i] - 'a'];
            cur->cnt++;
        }
    }
    
    //call pre first
    //return sum of cnt
    void getCnt () {
        vector<Node *> v;
        REP(i, 1, cnt) {
            v.PB (&no[i]);
        }
        sort (all(v), [] (const Node *a, const Node *b) {
            return a->len > b->len;
        });
        REP(i, 0, sz (v)) {
            v[i]->fail->cnt += v[i]->cnt;
        }
    }
    
    ll getNumOfDistinctSubstrings () {
        ll ans = 0;
        REP(i, 1, cnt)ans += no[i].len - no[i].fail->len;
        return (ans);
    }
};
