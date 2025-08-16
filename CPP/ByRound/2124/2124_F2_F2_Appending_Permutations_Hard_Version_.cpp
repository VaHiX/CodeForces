/*
 * Problem URL : https://codeforces.com/problemset/problem/2124/F2
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>
#include <immintrin.h>

using namespace std;

using ll = long long;
using ld = long double;
# define x first
# define y second
# define all(x) x.begin(), x.end()
# define rall(x) x.rbegin(), x.rend()

mt19937 mt(123);

void solve();
void init();

int32_t main() {
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    cout << fixed << setprecision(30);
    init();
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}

void init() {}

constexpr int mod = 998'244'353;

int add(int a, int b) {
    return a + b >= mod ? a + b - mod : a + b;
}

int sub(int a, int b) {
    return a >= b ? a - b : a + mod - b;
}

int mul(int a, int b) {
    return 1ll * a * b % mod;
}

int bin_pow(int a, int x) {
    int res = 1;
    while (x) {
        if (x & 1) {
            res = mul(res, a);
        }
        a = mul(a, a);
        x >>= 1;
    }
    return res;
}

int inv(int a) {
    return bin_pow(a, mod - 2);
}

const int N = 5050;
int calc[N][N], dp[N], pl[N][N], value[N], hui[N][N];

void solve() {
    int n, m;
    cin >> n >> m;
    vector<set<int>> con(n);
    for (int i = 0; i < m; i++) {
        int idx, val;
        cin >> idx >> val; idx--; val--;
        con[idx].insert(val);
    }
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i] = 0;
    }

    for (int j = n; j >= 0; j--) {
        for (int v = 0; v < n; v++) {
            if (j == n) {
                calc[j][v] = n + 2;
            } else {
                if (con[j].find(v) != con[j].end()) {
                    calc[j][v] = j;
                } else if (v != n - 1) {
                    calc[j][v] = calc[j + 1][v + 1];
                } else {
                    calc[j][v] = n + 2;
                }
            }
        }
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            hui[i][j] = 0;
            pl[i][j] = 0;
        }
        value[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        for (int s = 0; i + s < n; s++) {
            if (calc[i][0] >= i + s + 1) {
                dp[i + s + 1] = add(dp[i + s + 1], sub(dp[i], hui[i][0]));
                hui[i + s + 1][s + 1] = add(hui[i + s + 1][s + 1], sub(dp[i], hui[i][0]));
            }
        }
        if (i) {
            for (int v : con[i - 1]) {
                int hru = i - 1;
                for (; v >= 0 && hru >= 0; v--, hru--) {
                    value[v] = sub(value[v], pl[hru][v]);
                    pl[hru][v] = 0;
                }
            }
        }
        for (int j = i + 1; j <= n; j++) {
            if (calc[i][0] < j) continue;

            int r = j - i;

            dp[j] = add(dp[j], value[r]);
        }
        for (int r = 1; r < n; r++) {
            pl[i][r] = sub(dp[i], hui[i][r]);
            value[r] = add(value[r], pl[i][r]);
        }
    }

    cout << dp[n] << '\n';
}
