/*
 * Problem URL : https://codeforces.com/contest/2136/problem/F2
 * Submit Date : 2025-08-30
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int q(const vector<int>& a) {
    int n = a.size();
    if (n == 0) {
        return 1;
    }
    if (n < 0 || n > 100000) {
        return 0;
    }
    cout << "? " << n;
    for (int x : a) {
        cout << " " << x;
    }
    cout << endl;
    int r;
    cin >> r;
    if (r == -1) {
        exit(0);
    }
    return r;
}

void solve() {
    const int N = 11343;
    const int B = 116;
    const int WMAX = 100000;
    vector<int> a1(N, B);
    int r1 = q(a1);
    if (r1 == 0) {
        int m = B * B;
        vector<int> a2(m, 1);
        int r2 = q(a2);
        int w = (m - 1) / (r2 - 1);
        cout << "! " << w << endl;
    } else {
        int kL = (N - 1) / r1 + 1;
        int kH = (r1 == 1) ? WMAX : (N - 1) / (r1 - 1);
        int L = kL * B;
        int R = min(WMAX, (kH + 1) * B - 1);
        if (L == R) {
            cout << "! " << L << endl;
            return;
        }
        vector<int> a2;
        a2.reserve(2 * (R - L));
        for (int x = 1; x <= R - L; ++x) {
            a2.push_back(L);
            a2.push_back(x);
        }
        int r2 = q(a2);
        int W = 2 * R - L - r2;
        cout << "! " << W << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
