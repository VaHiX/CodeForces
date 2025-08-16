/*
 * Problem URL : https://codeforces.com/problemset/problem/2124/H
 * Submit Date : 2025-08-14
 */

#pragma GCC optimize("O3,unroll-loops")

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <iomanip>
#include <numeric>
#include <cstring>

using namespace std;

#define int long long

#define pii pair<int, int>
#define F first
#define S second

#define all(x) begin(x), end(x)

#define smn(v, x) (v = min(v, x))
#define smx(v, x) (v = max(v, x))

int tests = 1;

const int MOD = 998244353;
const int INF = 2e18;

struct mod {
    int x;

    mod(int a=0): x(a % MOD) {}

    mod& operator+=(const mod& y) {
        x += y.x;

        if (x >= MOD) {
            x -= MOD;
        }

        return *this;
    }

    mod& operator-=(const mod& y) {
        x -= y.x;

        if (x < 0) {
            x += MOD;
        }

        return *this;
    }

    mod& operator*=(const mod& y) {
        x = (x * y.x) % MOD;

        return *this;
    }

    static mod exp(mod b, int e) {
        mod res = 1;

        for (; e; e >>= 1) {
            if (e & 1) {
                res *= b;
            }
            b *= b;
        }

        return res;
    }

    mod inv() const {
        return exp(*this, MOD - 2);
    }

    mod& operator/=(const mod& y) {
        return *this *= y.inv();
    }

    friend mod operator+(mod a, const mod& b) {
        return a += b;
    }

    friend mod operator-(mod a, const mod& b) {
        return a -= b;
    }

    friend mod operator*(mod a, const mod& b) {
        return a *= b;
    }

    friend mod operator/(mod a, const mod& b) {
        return a /= b;
    }

    friend bool operator==(const mod& a, const mod& b) {
        return a.x == b.x;
    }

    friend bool operator!=(const mod& a, const mod& b) {
        return a.x != b.x;
    }

    friend mod operator<<(int a, const mod& b) {
        return mod(a << b.x);
    }
};

const int N = 15003;

int n, m;

int a[N];

vector<int> pos[N];

short dp[N][N];

void solve(int i) {
    if (dp[i][i]) {
        return;
    }

    dp[i][i] = a[i];
    for (int p = i; p; ) {
        if (p != i) {
            dp[i][p] = dp[i][p - 1] + 1;
        }

        int j = 0;
        for (int k = p + 1; k <= n; k++) {
            if (a[k] == a[i]) {
                j = k;
                break;
            }
            smx(dp[i][k], dp[i][p]);
        }

        int val = dp[i][p] + 1;
        if (!pos[val].empty() && pos[val].back() > p) {
            int idx = *upper_bound(all(pos[val]), p);

            solve(idx);

            for (int k = idx; k <= n; k++) {
                smx(dp[i][k], dp[idx][k]);
            }
        }

        p = j;
    }

    // cout << i << ": "; for (int j = 1; j <= n; j++) cout << dp[i][j] << ' '; cout << '\n';
}

void run()
{
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i], pos[a[i]].push_back(i);
    }

    if (pos[1].empty()) {
        cout << 0 << '\n';
    }
    else {
        solve(pos[1][0]);

        cout << dp[pos[1][0]][n] << '\n';
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 0; i <= n; i++) {
        pos[i].clear();
    }
}

signed main()
{
    ios::sync_with_stdio(0);

    cin.tie(0);
    cout.tie(0);

    cin >> tests;
    while (tests--)
    {
        run();
    }

    return 0;
}
