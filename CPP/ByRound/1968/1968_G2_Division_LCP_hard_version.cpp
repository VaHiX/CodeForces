// Problem: CF 1968 G2 - Division + LCP (hard version)
// https://codeforces.com/contest/1968/problem/G2

/*
 * Problem: G2. Division + LCP (hard version)
 * 
 * Purpose: Given a string s and a range [l, r], compute f_k for all k in [l, r],
 *          where f_k is the maximum LCP (Longest Common Prefix) of any division
 *          of s into exactly k continuous substrings.
 * 
 * Algorithm:
 *   - Uses Z-algorithm to compute z-array for efficient substring comparisons.
 *   - Uses Union-Find (DSU) to efficiently group positions with common prefix lengths.
 *   - For each possible k, compute the maximum LCP over all valid divisions.
 * 
 * Time Complexity: O(n log n) per test case due to sorting and DSU operations
 * Space Complexity: O(n) for storing z-array, DSU, and auxiliary structures
 */

#include <stdio.h>
#include <algorithm>
#include <random>
#include <utility>
#include <vector>

using namespace std;
#define oo 1000000010
#define mod 998244353
const int N = 200010;
int n, a, b;
char s[N];
vector<int> build_z(int n, char *s) {
  vector<int> z(n);
  int l = 0, r = 0;
  z[0] = n;
  for (int i = 1; i < n; i++) {
    if (i >= r) {
      l = r = i;
      while (r < n && s[r - i] == s[r])
        r++;
      z[i] = r - l;
      continue;
    }
    if (i + z[i - l] < r) {
      z[i] = z[i - l];
      continue;
    }
    l = i;
    while (r < n && s[r - i] == s[r])
      r++;
    z[i] = r - l;
  }
  return z;
}
int dsu[N];
int Find(int u) { return (u == dsu[u] ? u : dsu[u] = Find(dsu[u])); }
void Union(int a, int b) {
  a = Find(a);
  b = Find(b);
  dsu[a] = b;
}
void solve() {
  scanf("%d%d%d", &n, &a, &b);
  scanf("%s", s);
  vector<int> z = build_z(n, s);
  vector<pair<int, int>> v;
  for (int i = 0; i < n; i++) {
    v.push_back(make_pair(z[i], i));
  }
  sort(v.begin(), v.end());
  int last = 0;
  for (int i = 0; i <= n; i++)
    dsu[i] = i;
  vector<int> ans(n + 1, 0);
  for (int cur, idx, k = 1; k <= n; k++) {
    while (last < (int)v.size() && v[last].first < k) {
      Union(v[last].second, v[last].second + 1);
      last++;
    }
    idx = k;
    cur = 1;
    while (idx < n) {
      idx = Find(idx);
      if (idx == n)
        break;
      idx += k;
      cur++;
    }
    ans[cur] = k;
  }
  for (int i = n - 1; i >= 0; i--)
    ans[i] = max(ans[i], ans[i + 1]);
  for (int i = a; i <= b; i++)
    printf("%d ", ans[i]);
  puts("");
}
int main() {
  int t;
  scanf("%d", &t);
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/