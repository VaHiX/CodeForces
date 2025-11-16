// Problem: CF 1847 F - The Boss's Identity
// https://codeforces.com/contest/1847/problem/F

/*
Code Purpose:
This code solves a problem where we have an infinite sequence defined by a pattern of n initial elements. 
For indices beyond n, each element is the bitwise OR of the previous n elements. 
We are tasked to answer q queries, each asking for the smallest index where the value in the sequence exceeds a given threshold.

Algorithms/Techniques:
- Bitwise OR operations
- Queue-based processing to compute values
- Binary search on the computed sequence
- Efficient generation and storage of the sequence using the defined recurrence relation

Time Complexity:
O(n * B + q * log(n)) where B = 31 (number of bits in integer)
Space Complexity:
O(n * B + n) for the visited array and vector of pairs
*/

#include <string.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
#define ll long long
#define ull unsigned long long
#define pb(e) push_back(e)
#define sv(a) sort(a.begin(), a.end())
#define sa(a, n) sort(a, a + n)
#define mp(a, b) make_pair(a, b)
#define vf first
#define vs second
#define all(x) x.begin(), x.end()
const int B = 31;
struct item {
  ll pos, bit, idx;
};
item make(ll pos, ll bit, ll idx) {
  item res;
  res.pos = pos;
  res.bit = bit;
  res.idx = idx;
  return res;
}
void solve() {
  int n;
  cin >> n;
  int qu;
  cin >> qu;
  int arr[n];
  for (int i = 0; i < n; i++)
    cin >> arr[i];
  if (n == 1) {
    while (qu--) {
      int x;
      cin >> x;
      if (x < arr[0])
        cout << 1 << '\n';
      else
        cout << -1 << '\n';
    }
    return;
  }
  vector<pair<ll, ll>> v;
  queue<item> q;
  bool vis[n][B];
  memset(vis, 0, sizeof vis);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < B; j++) {
      if ((arr[i] & (1 << j)) > 0) {
        vis[i][j] = 1;
      }
    }
    v.pb(mp(i, arr[i]));
  }
  for (int i = 0; i < n - 1; i++) {
    v.pb(mp(n + i, arr[i] | arr[i + 1]));
  }
  for (int j = 0; j < B; j++) {
    if (vis[n - 1][j])
      q.push(make(n + n - 1, j, 0));
  }
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < B; j++) {
      if (vis[i][j])
        q.push(make(n + n + i, j, (i + 1) % (n - 1)));
    }
  }
  int val[n - 1];
  for (int i = 0; i < n - 1; i++)
    val[i] = arr[i] | arr[i + 1];
  while (q.size()) {
    item it = q.front();
    q.pop();
    if ((val[it.idx] & (1 << it.bit)) > 0) {
      continue;
    }
    val[it.idx] += (1 << it.bit);
    if (v.back().vf == it.pos) {
      v.pop_back();
    }
    v.pb(mp(it.pos, val[it.idx]));
    q.push(make(it.pos + n, it.bit, (it.idx + 1) % (n - 1)));
  }
  for (int i = 1; i < v.size(); i++) {
    v[i].vs = max(v[i].vs, v[i - 1].vs);
  }
  while (qu--) {
    int x;
    cin >> x;
    ll l = 0, r = v.size() - 1;
    ll res = -1;
    while (l <= r) {
      int mid = (l + r) / 2;
      if (v[mid].vs <= x) {
        l = mid + 1;
      } else {
        r = mid - 1;
        res = v[mid].vf + 1;
      }
    }
    cout << res << '\n';
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/