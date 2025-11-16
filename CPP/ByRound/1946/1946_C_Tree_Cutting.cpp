// Problem: CF 1946 C - Tree Cutting
// https://codeforces.com/contest/1946/problem/C

/*
 * Problem: Tree Cutting
 * Algorithm: Binary search + DFS
 * Time Complexity: O(n * log(n)) per test case
 * Space Complexity: O(n)
 *
 * Approach:
 * - We want to find the maximum x such that we can remove exactly k edges 
 *   so that all remaining connected components have at least x nodes.
 * - Use binary search on the answer (x).
 * - For a fixed x, check if it's possible to split the tree into at least k+1 
 *   components, each having size >= x, by removing exactly k edges.
 * - Use DFS to count how many valid components we can form with size >= x.
 * - If we can form more than k components, it means we can remove k edges 
 *   and still keep components of size x or more.
 */

#include <stdio.h>
#include <iostream>

using namespace std;
#define ls(u) tr[u].son[0]
#define rs(u) tr[u].son[1]
typedef long long ll;
char *p1, *p2, buf[100000];
#define nc()                                                                   \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2)      \
       ? EOF                                                                   \
       : *p1++)
inline int read() {
  int x = 0, f = 1;
  char ch = nc();
  while (ch < 48 || ch > 57) {
    if (ch == '-')
      f = -1;
    ch = nc();
  }
  if (ch == '-')
    f = -1;
  while (ch >= 48 && ch <= 57)
    x = (x << 1) + (x << 3) + (ch ^ 48), ch = nc();
  return f * x;
}
inline void write(int x) {
  if (x < 0)
    x = -x, putchar('-');
  if (x < 10)
    putchar(x ^ 48);
  else
    write(x / 10), write(x % 10);
}
int pt;
inline void read(char *opt) {
  char ch = nc();
  while ((ch < 65 || ch > 90) && (ch > 132 || ch < 97) && ch != '*')
    ch = nc();
  while (ch >= 65 && ch <= 90 || ch >= 97 && ch <= 132 || ch == '*')
    opt[pt++] = ch, ch = nc();
  opt[pt] = 0, pt = 0;
}
inline int max(const int &x, const int &y) {
  if (x > y)
    return x;
  return y;
}
inline int min(const int &x, const int &y) {
  if (x < y)
    return x;
  return y;
}
const int N = 1e5 + 10, M = 2 * N, mod = 1e9 + 7;
int h[N], e[M], ne[M], idx;
int n, k, sz[N];
void add(int a, int b) { e[idx] = b, ne[idx] = h[a], h[a] = idx++; }
int dfs(int u, int p, int mx) {
  sz[u] = 1;
  int cnt = 0;
  for (int i = h[u]; ~i; i = ne[i]) {
    int j = e[i];
    if (j == p)
      continue;
    cnt += dfs(j, u, mx);
    sz[u] += sz[j];
  }
  if (sz[u] >= mx)
    cnt++, sz[u] = 0;
  return cnt;
}
bool check(int mid) {
  int cnt = dfs(1, 0, mid) - 1;
  return cnt >= k;
}
inline void solve() {
  n = read(), k = read();
  idx = 0;
  for (int i = 1; i <= n; i++)
    h[i] = -1;
  for (int i = 0; i < n - 1; i++) {
    int a = read(), b = read();
    add(a, b), add(b, a);
  }
  int l = 1, r = n + 1;
  while (r - l != 1) {
    int mid = l + r >> 1;
    if (check(mid))
      l = mid;
    else
      r = mid;
  }
  cout << l << "\n";
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int testcase;
  testcase = read();
  while (testcase--)
    solve();
}


// https://github.com/VaHiX/CodeForces/