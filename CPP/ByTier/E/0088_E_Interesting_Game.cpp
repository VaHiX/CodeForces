/*
 * Problem URL : https://codeforces.com/problemset/problem/88/E
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;

#define pb push_back
#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define forrn(i, s, n) for (int i = (int)(s); i < (int)(n); i++)
#define PYMOD(a, m) ((((a) % (m)) + (m)) % (m))
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define mp make_pair
#define ff first
#define ss second

const int maxn = 100179;
int dp[maxn];

int value(int n) {
    if (dp[n] == -1) {
        vector<int> values;
        for (int k = 2; k * (k + 1) / 2 <= n; k++) {
            if ((n - k * (k + 1) / 2) % k == 0) {
                int b = (n - k * (k + 1) / 2) / k;
                int v = 0;
                forrn(i, 1, k + 1) {
                    v ^= value(b + i);
                }
                values.pb(v);
            }
        }
        sort(all(values));
        values.resize(unique(all(values)) - values.begin());
        int i = 0;
        for(; i < (int)values.size() && values[i] == i; i++);
        dp[n] = i;
    }
    return dp[n];
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    // Code here:
    memset(dp, 0xff, sizeof(dp));

    int n;
    cin >> n;
    if (value(n)) {
        for (int k = 2; k * (k + 1) / 2 <= n; k++) {
            if ((n - k * (k + 1) / 2) % k == 0) {
                int b = (n - k * (k + 1) / 2) / k;
                int v = 0;
                forrn(i, 1, k + 1) {
                    v ^= value(b + i);
                }
                if (v == 0) {
                    cout << k << endl;
                    return 0;
                }
            }
        }
    } else {
        cout << -1 << endl;
    }

    return 0;
}
