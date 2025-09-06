/*
 * Problem URL : https://codeforces.com/problemset/problem/2115/D
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    vector<ll> a;
    ll Bas = 0;
    string s;
    cin >> n;
    a.resize(n);
    for (auto &k : a)
      cin >> k, Bas ^= k;
    for (auto &k : a) {
      ll x;
      cin >> x;
      k ^= x;
    }
    cin >> s;
    for (int z = 59; z >= 0; z--) {
      int p = -1;
      for (int i = n - 1; i >= 0; i--)
        if (a[i] >> z & 1) {
          if (p == -1)
            p = i;
          else
            a[i] ^= a[p];
        }
      if (p == -1)
        continue;
      if (s[p] == '0')
        Bas = min(Bas, Bas ^ a[p]);
      else
        Bas = max(Bas, Bas ^ a[p]);
      a[p] = 0;
    }
    cout << Bas << '\n';
  }
}