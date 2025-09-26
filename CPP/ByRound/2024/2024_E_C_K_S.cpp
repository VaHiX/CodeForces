/*
 * Problem URL : https://codeforces.com/contest/2024/problem/E
 * Submit Date : 2025-09-10
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <set>
#include <cmath>

#define vc vector
#define pip pair <int, int>
#define pb push_back
#define ll long long
#define mp(a, b) make_pair(a, b)
#define all(s) s.begin(), s.end()

const int inf = 1e9 + 7;
const ll INF = 1e18;

using namespace std;

vc <vc <int>> g;

void dfs(int v, vc <int> & t) {
    for (int i = 0; i < g[v].size(); i++) {
        int u = g[v][i];
        if (t[u]) continue;
        t[u] = t[v] + 1;
        dfs(u, t);
    }
}

void roll (vc <int> & arr) {
    int n = arr.size();
    for (int i = n-1; i > 0; i--) swap(arr[i], arr[i-1]);
}

vc <int> f(vc <int> & a, vc <int> & b) {
    int n = a.size();
    vc <int> s;

    for (int i = 0; i < n; i++) s.pb(b[i]);
    for (int i = 0; i < 2*n; i++) s.pb(a[i%n]);

    n *= 3;
    vc <int> h(n);
    int l = 0, r = -1;

    for (int i = 1; i < n; i++) {
        if (i <= r) h[i] = min(r-i+1, h[i-l]);
        while (i + h[i] < n && s[i + h[i]] == s[h[i]]) h[i]++;
        if (r < i + h[i] - 1) r = i + h[i] - 1, l = i;
    }

    return h;
}

void solve () {
    int n, k, m;
    cin >> n >> k;

    g.resize(n);
    vc <int> t1(n), t2(n);
    for (int i = 0; i < n; i++) g[i].resize(0);

    vc <int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    cin >> m;
    while (m--) {
        int v, u;
        cin >> v >> u;
        v--, u--;
        g[v].pb(u);
    }
    dfs(0, t1);

    for (int i = 0; i < n; i++) g[i].resize(0), cin >> b[i];

    cin >> m;
    //cout << m << ' ';
    while (m--) {
        int v, u;
        cin >> v >> u;
        v--, u--;
        g[v].pb(u);
    }
    dfs(0, t2);

    for (int i = 0; i < n; i++) t1[i] %= k, t2[i] %= k;

    int res = 0;
    vc <int> q1(k), q0(k), w1(k), w0(k);
    for (int i = 0; i < n; i++) {
        if (a[i]) q1[t1[i]]++;
        else q0[t1[i]]++;
        if (b[i]) w1[t2[i]]++;
        else w0[t2[i]]++;
    }

    for (int i = 0; i < n; i++) res += a[i] - b[i];
    if (abs(res) == n) {
        cout << "yes\n";
        return;
    }

    roll(q1);
    roll(w1);

    vc <int> ans1 = f(q1, w0), ans2 = f(q0, w1);

    for (int i = k; i < 3*k; i++) {
        if (min(ans1[i], ans2[i]) >= k) {
            cout << "YES\n";
            return;
        }
    }


    //cout << "\n";
    cout << "No\n";
}

int main() {
    ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);

    int test = 1;
    cin >> test;

    while (test--) {
        solve();
    }

    return 0;
}