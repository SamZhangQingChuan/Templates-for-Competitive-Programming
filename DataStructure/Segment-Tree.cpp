struct SegTree {
    static const int maxn =;
    
    struct node {
        int l, r;
    };
    
    node no[maxn * 4];
    
    void push_up(int ind) {
    
    }
    
    void push_down(int ind) {
    }
    
    void build(int l, int r, int ind) {
        no[ind].l = l;
        no[ind].r = r;
        if(l == r) {
        
        } else {
            int mid = (l + r) / 2;
            build(l, mid, lson);
            build(mid + 1, r, rson);
            push_up(ind);
        }
    }
    
    void update(int l, int r, int ind, int val) {
        if(l > no[ind].r || r < no[ind].l)return;
        if(l <= no[ind].l && no[ind].r <= r) {
        } else {
            push_down(ind);
            update(l, r, lson, val);
            update(l, r, rson, val);
            push_up(ind);
        }
    }
    
    void query(int l, int r, int ind, int &ans) {
        if(l > no[ind].r || r < no[ind].l)return;
        if(l <= no[ind].l && no[ind].r <= r) {
            
        } else {
            push_down(ind);
            query(l, r, lson, ans);
            query(l, r, rson, ans);
            push_up(ind);
            
        }
    }
};

//[l,r) everywhere
struct DynamicSegtree {
    struct Node {
        Node *son[2];
        ll l, r;
        
        Node(ll l, ll r) : l(l), r(r) {
            son[0] = son[1] = nullptr;
        }
        
        
        void push_down() {
            REP(i, 0, 2)
            {
                if(son[i] == nullptr) {
                    if(i == 0)son[0] = new Node(l, (l + r) / 2);
                    if(i == 1)son[1] = new Node((l + r) / 2, r);
                }
            }
        }
        
        void push_up() {
            REP(i, 0, 2)
            {
                if(son[i] != nullptr) {
                
                }
            }
        }
    };
    
    Node *root;
    
    DynamicSegtree(int l, int r) {
        root = new Node(l, r);
    }
    
    
    void update(int l, int r, Node *no, ll val) {
        if(no == nullptr or l >= no->r or r <= no->l)return;
        if(l <= no->l and no->r <= r) {
        
        } else {
            no->push_down();
            REP(i, 0, 2)
            {
                update(l, r, no->son[i], val);
            }
            no->push_up();
        }
    }
    
    void query(int l, int r, Node *no, ll &ans) {
        if(no == nullptr or l >= no->r or r <= no->l)return;
        if(l <= no->l and no->r <= r) {
        
        } else {
            no->push_down();
            REP(i, 0, 2)
            {
                query(l, r, no->son[i], ans);
            }
            no->push_up();
        }
    }
};

