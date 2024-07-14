#include <string>
#include <vector>
#include <algorithm>

void calcNext(const std::string &s, int nxt[]) {
    int p = nxt[0] = -1;
    for (int i = 1; i < s.size(); i++) {
        while (p != -1 && s[p + 1] != s[i])p = nxt[p];
        p += s[p + 1] == s[i];
        nxt[i] = p;
    }
}


std::vector<int> exkmp(const std::string &s) {
    int n = s.size();
    std::vector<int> z(n);
    int x = 0, y = 0;
    for (int i = 1; i < n; i++) {
        z[i] = std::max(0, std::min(z[i - x], y - i + 1));
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            x = i;
            y = i + z[i];
            z[i]++;
        }
    }
    z[0] = n;
    return z;
}
