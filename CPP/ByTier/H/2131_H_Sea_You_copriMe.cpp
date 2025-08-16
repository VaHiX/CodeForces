/*
 * Problem URL : https://codeforces.com/problemset/problem/2131/H
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 1000 << 10;
vector<int> primes, minp;
int cnt[MAXN];

void sieve() {
    minp.assign(MAXN, 0);
    for (int i = 2; i < MAXN; i++) {
        if (!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > minp[i] || 1LL * i * p >= MAXN) break;
            minp[i * p] = p;
        }
    }
}

vector<int> getDivisors(int x) {
    vector<int> res = {1};
    while (x > 1) {
        int p = minp[x];
        int sz = res.size();
        for (int i = 0; i < sz; i++) res.push_back(res[i] * p);
        while (x % p == 0) x /= p;
    }
    return res;
}

void solve() {
    int n, u;
    cin >> n >> u;

    fill(cnt, cnt + u + 1, 0);
    vector<int> a(n);
    for (int &x : a) {
        cin >> x;
        cnt[x]++;
    }

    for (int p : primes) {
        if (p > u) break;
        for (int i = u / p; i >= 1; i--) cnt[i] += cnt[i * p];
    }

    vector<int> deg(n, 0);
    for (int i = 0; i < n; i++) {
        if (a[i] == 1) {
            deg[i] = n - 1;
            continue;
        }
        auto divs = getDivisors(a[i]);
        int c = 0;
        for (int idx = 0; idx < (int)divs.size(); idx++) {
            if (__builtin_popcount(idx) & 1) c -= cnt[divs[idx]];
            else c += cnt[divs[idx]];
        }
        deg[i] = c;
    }

    ll sumDeg = accumulate(deg.begin(), deg.end(), 0LL);
    int mx = *max_element(deg.begin(), deg.end());

    if (sumDeg < 4 || mx * 2 == sumDeg) {
        cout << 0 << endl;
        return;
    }

    int x = 0, y = 0;
    for (int i = 0; i < n && !x; i++) if (deg[i]) {
        for (int j = 0; j < n; j++) if (j != i) {
            if (gcd(a[i], a[j]) == 1 && (deg[i] + deg[j] - 1) * 2 != sumDeg) {
                x = i + 1; y = j + 1;
                break;
            }
        }
    }
    if (!x) {
        cout << 0 << endl;
        return;
    }

    for (int i = 0; i < n; i++) if (i != x - 1 && i != y - 1) {
        int c = deg[i];
        c -= (gcd(a[x - 1], a[i]) == 1);
        c -= (gcd(a[y - 1], a[i]) == 1);
        if (!c) continue;
        for (int j = 0; j < n; j++) if (j != x - 1 && j != y - 1 && j != i && gcd(a[i], a[j]) == 1) {
            cout << x << " " << y << " " << i + 1 << " " << j + 1 << endl;
            return;
        }
    }
    cout << 0 << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve();
    int T;
    cin >> T;
    while (T--) solve();
}
