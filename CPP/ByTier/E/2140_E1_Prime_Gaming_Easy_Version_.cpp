/*
 * Problem URL : https://codeforces.com/contest/2140/problem/E1
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1000000007;
ll powmod(ll a, int e) {
  ll r = 1;
  while (e) {
    if (e & 1)
      r = r * a % MOD;
    a = a * a % MOD;
    e >>= 1;
  }
  return r;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  if (!(cin >> t))
    return 0;
  while (t--) {
    int n;
    int m;
    cin >> n >> m;
    int k;
    cin >> k;
    vector<int> c(k);
    for (int i = 0; i < k; i++)
      cin >> c[i];
    if (m == 1) {
      cout << 1 << "\n";
      continue;
    }
    vector<char> prev;
    prev.resize(2);
    prev[0] = 1;
    prev[1] = 0;
    vector<int> gs;
    int ptr = 0;
    if (c[ptr] == 1) {
      gs.push_back(0);
      ptr++;
    }
    for (int p = 2; p <= n; p++) {
      while (ptr < k && c[ptr] <= p) {
        gs.push_back(c[ptr] - 1);
        ptr++;
      }
      int sz = 1 << p;
      vector<char> cur(sz, 0);
      for (int mask = 0; mask < sz; mask++) {
        char lose = 1;
        for (int b : gs) {
          if (b >= p)
            break;
          int low = mask & ((1 << b) - 1);
          int high = mask >> (b + 1);
          int nxt = low | (high << b);
          if (prev[nxt]) {
            lose = 0;
            break;
          }
        }
        cur[mask] = lose;
      }
      prev.swap(cur);
    }
    int cnt = 0;
    int fn = 1 << n;
    for (int i = 0; i < fn; i++)
      if (prev[i])
        cnt++;
    ll tot = (powmod(2, n + 1) - (cnt % MOD) + MOD) % MOD;
    cout << tot << "\n";
  }
  return 0;
}