/*** Manacher's algorithm to generate longest palindromic substrings for all centers ***/
/// When i is even, pal[i] = largest palindromic substring centered from str[i / 2]
/// When i is odd, pal[i] = largest palindromic substring centered between str[i / 2] and str[i / 2] + 1
//  manacher(string("1222112"))
//  1 0 1 2 5 2 1 0 1 4 1 0 1
template<typename T>
VI manacher(const T &str) { /// hash = 784265
    int i, j, k, l = sz(str), n = l << 1;
    VI pal(n);
    if (!sz(str))return pal;
    for (i = 0, j = 0, k = 0; i < n; j = max(0, j - k), i += k) {
        while (j <= i && (i + j + 1) < n && str[(i - j) >> 1] == str[(i + j + 1) >> 1]) j++;
        for (k = 1, pal[i] = j; k <= i && k <= pal[i] && (pal[i] - k) != pal[i - k]; k++) {
            pal[i + k] = min(pal[i - k], pal[i] - k);
        }
    }
    
    pal.pop_back();
    return pal;
}
