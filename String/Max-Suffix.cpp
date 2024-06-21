
int getMaxSuffix(const string &s) {
    int len = sz(s);
    int ans = 0;
    int cur = 1;
    while (cur < len) {
        if (ans == cur)cur++;
        int i = cur;
        while (i < len) {
            if (s[i] != s[ans + i - cur]) {
                if (s[i] < s[ans + i - cur]) {
                    cur = i + 1;
                } else {
                    int tmp = ans;
                    ans = cur;
                    cur = tmp + i - cur + 1;
                }
                break;
            }
            i++;
        }
        if (i == len) {
            return ans;
        }
    }
    return ans;
}

