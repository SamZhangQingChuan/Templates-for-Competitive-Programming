PLL operator-(const PLL &a, const PLL &b) {
    return MP(a.fi - b.fi, a.se - b.se);
}

PLL operator+(const PLL &a, const PLL &b) {
    return MP(a.fi + b.fi, a.se + b.se);
}

// counter-clockwise is positive
ll cp(PLL o, PLL a, PLL b) {
    a = a - o;
    b = b - o;
    return a.fi * b.se - a.se * b.fi;
}


vector <PLL> upper_convex_hull(vector <PLL> points) {
    sort(all(points), [](const PLL &a, const PLL &b) {
        if (a.fi != b.fi)return a.fi < b.fi;
        return a.se < b.se;
    });
    vector <PLL> ans;
    for (auto i:points) {
        if (sz(ans) and ans.back().fi == i.fi)ans.pop_back();
        while (sz(ans) >= 2 and cp(ans[sz(ans) - 2], ans.back(), i) >= 0) {
            ans.pop_back();
        }
        ans.PB(i);
    }
    return ans;
}

vector <PLL> lower_convex_hull(vector <PLL> points) {
    sort(all(points), [](const PLL &a, const PLL &b) {
        if (a.fi != b.fi)return a.fi < b.fi;
        return a.se > b.se;
    });
    vector <PLL> ans;
    for (auto i:points) {
        if (sz(ans) and ans.back().fi == i.fi)ans.pop_back();
        while (sz(ans) >= 2 and cp(ans[sz(ans) - 2], ans.back(), i) <= 0) {
            ans.pop_back();
        }
        ans.PB(i);
    }
    return ans;
}
