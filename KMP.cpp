void calcNext(const string &s, int nxt[]) {
    int p = nxt[0] = -1;
    REP(i, 1, sz(s)){
        while (p != -1 && s[p + 1] != s[i])p = nxt[p];
        p += s[p + 1] == s[i];
        nxt[i] = p;
    }
}


vector<int> exkmp(const string &s) {
    int n = s.size();
    vector<int> z(n);
    int x = 0, y = 0;
    for(int i = 1; i < n; i++) {
        z[i] = max(0, min(z[i - x], y - i + 1));
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            x = i;
            y = i + z[i];
            z[i]++;
        }
    }
    z[0] = n;
    return z;
}
