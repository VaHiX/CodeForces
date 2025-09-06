/*
 * Problem URL : https://codeforces.com/contest/2134/problem/B
 * Submit Date : 2025-08-30
 */

#include <iostream>
using namespace std;
int t, n, k;
int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    for (cin >> t; t; --t) {
        cin >> n >> k;
        for (int i = 1, a; i <= n; ++i)
            cin >> a, cout << a + 1ll * k * (a % (k + 1)) << " \n"[i == n];
    }
}