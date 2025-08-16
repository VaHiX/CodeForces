/*
 * Problem URL : https://codeforces.com/problemset/problem/2120/G
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h> 
using namespace std;
typedef long long ll;

int xx = 0;

void solve() {  
    xx++;
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> arr(n);
    vector<array<int, 2>> edges(m);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        arr[a].push_back(b);
        arr[b].push_back(a);
        edges[i] = {a, b};
    }
    function<bool()> cyc = [&]() {
        int odd = 0;
        for (int i = 0; i < n; i++) {
            odd += arr[i].size() % 2;
        }
        if (odd == 0) return true;
        for (int i = 0; i < n; i++) {
            for (int x : arr[i]) {
                if ((arr[i].size() - 1) % 2 == (arr[x].size() - 1) % 2) {
                    return false;
                }
            }
        }
        if (k >= 2) return true;
        return false;
    };
    function<bool()> oth = [&]() {
        int f, s;
        f = s = -1;
        for (int i = 0; i < n; i++) {
            if (arr[i].size() % 2) {
                s = (f != -1 ? i : s);
                f = (f == -1 ? i : f);
            }
        }
        int a1, a2;
        a1 = a2 = 0;
        function<int(int u, int p)> calc = [&](int u, int p) {
            if (arr[u].size() > 2) return 0;
            return 1 + (arr[u][0] == p ? calc(arr[u][1], u) : calc(arr[u][0], u));
        };
        a1 = calc(f, -1);
        a2 = calc(s, -1);
        if (a1 > a2) {
            swap(a1, a2);
            swap(f, s);
        }
        if (a1 >= k) return true;
        if (a1 > 0) return false;
        if (a2 == 1 && arr[s].size() == 3 && arr[f][0] == s) {
            return k == 1;
        }
        if (k >= 3 || k == 1) return false;
        ll cnt = 0;
        vector<array<int, 2>> val(n);
        for (int i = 0; i < m; i++) {
            val[edges[i][0]][arr[edges[i][1]].size() % 2]++;
            val[edges[i][1]][arr[edges[i][0]].size() % 2]++;
        }
        for (int i = 0; i < n; i++) cnt += (1ll * val[i][0] * val[i][1]);
        return cnt == 2;
    };
    
    cout << (cyc() || oth() ? "YES\n" : "NO\n");
}
 
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1; 
    cin >> t;
    while(t--) {
        solve();
    }
}