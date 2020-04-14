void calcNext(const string &s, int nxt[]) {
    int p = nxt[0] = -1;
    REP(i, 1, sz(s))
    {
        while (p != -1 && s[p + 1] != s[i])p = nxt[p];
        p += s[p + 1] == s[i];
        nxt[i] = p;
    }
}


/**
 * z[i] = lcp(s[i:], s[0:])
 *
 * time complexity: O(n)
 **/
std::vector<int> ext_kmp(char *s, int n) {
    std::vector<int> z(n, 0);
    for (int i = 1, x = 0, y = 0; i < n; ++i) {
        if (i <= y) z[i] = std::min(y - i, z[i - x]);
        while (i + z[i] < n && s[i + z[i]] == s[z[i]]) ++z[i];
        if (y <= i + z[i]) x = i, y = i + z[i];
    }
    z[0] = n;
    return z;
}
