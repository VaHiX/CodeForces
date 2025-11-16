// Problem: CF 1975 D - Paint the Tree
// https://codeforces.com/contest/1975/problem/D

/*
 * Problem: Paint the Tree
 * Algorithm: Tree diameter and BFS-based analysis of painting process.
 * 
 * Key Insight:
 * - P_A moves first and paints red any white node it lands on.
 * - P_B moves second and paints blue any red node it lands on.
 * - Goal is to paint all nodes blue in minimum steps.
 * 
 * Approach:
 * 1. Build the tree from input edges.
 * 2. Find the path from b to a using DFS (t array stores parent in path).
 * 3. Compute the middle point of this path as the root (to minimize max distance).
 * 4. Perform BFS from this root to find maximum distance (tree diameter).
 * 5. The answer is: (n - 1) * 2 - max_dist + steps_to_root
 * 
 * Time Complexity: O(n) per test case due to tree traversal and BFS.
 * Space Complexity: O(n) for storing tree and auxiliary arrays.
 */

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <utility>

#define SEQ 19
using namespace std;
typedef pair<long long, int> pli;
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef pair<int, pii> piii;
typedef pair<int, long long> pil;
typedef long long ll;
const int N = 2000086, MOD = 1e9 + 7, INF = 0x3f3f3f3f, MID = 333, M = 1000086;
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
int n, m, cnt, w[N];
vector<int> num;
ll res;
int lowbit(int x) { return x & -x; }
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
inline double rand(double l, double r) {
  return (double)rand() / RAND_MAX * (r - l) + l;
}
inline ll qmi(ll a, ll b, ll c) {
  ll res = 1;
  while (b) {
    if (b & 1)
      res = res * a % c;
    a = a * a % c;
    b >>= 1;
  }
  return res;
}
inline ll qmi(ll a, ll b) {
  ll res = 1;
  while (b) {
    if (b & 1)
      res *= a;
    a *= a;
    b >>= 1;
  }
  return res;
}
inline double qmi(double a, ll b) {
  double res = 1;
  while (b) {
    if (b & 1)
      res *= a;
    a *= a;
    b >>= 1;
  }
  return res;
}
inline int _find(int x) {
  return lower_bound(num.begin(), num.end(), x) - num.begin();
}
int idx;
int e[N], ne[N], h[N], a, b, t[N], root, d[N];
bool st[N];
inline void add(int a, int b) { e[idx] = b, ne[idx] = h[a], h[a] = idx++; }
inline bool dfs(int r, int fa) {
  if (r == a)
    return true;
  for (int i = h[r]; i != -1; i = ne[i]) {
    int j = e[i];
    if (j == fa)
      continue;
    if (dfs(j, r)) {
      t[r] = j;
      return true;
    }
  }
  return false;
}
inline void dfs2(int r, int fa) {
  for (int i = h[r]; i != -1; i = ne[i]) {
    int j = e[i];
    if (j == fa)
      continue;
    d[j] = d[r] + 1;
    dfs2(j, r);
  }
}
int main() {
  int T;
  cin >> T;
  while (T--) {
    scanf("%d", &n);
    scanf("%d%d", &a, &b);
    memset(h, -1, sizeof(int) * (n + 10));
    idx = 0;
    for (int i = 1; i < n; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      add(a, b), add(b, a);
    }
    dfs(b, -1);
    int len = 0, tmp = b;
    while (tmp != a) {
      len++;
      tmp = t[tmp];
    }
    len = (len + 1) >> 1;
    root = b;
    int delta = len;
    while (len--)
      root = t[root];
    d[root] = 0;
    dfs2(root, -1);
    res = 0;
    for (int i = 1; i < n + 1; i++)
      res = max(res, (ll)d[i]);
    printf("%lld\n", (n - 1) * 2 - res + delta);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/