// Problem: CF 1975 F - Set
// https://codeforces.com/contest/1975/problem/F

/*
 * Problem: Find all sets S ⊆ {0, 1, ..., n-1} such that for every non-empty subset T ⊆ {0, 1, ..., n-1},
 *          the size of S ∩ T belongs to the set V_{f(T)} where f(T) is the binary encoding of T.
 *
 * Algorithm:
 * - The key insight is to utilize a recursive approach to build valid sets S.
 * - We represent the input as a binary tree where each node corresponds to a subset of elements.
 * - For every subset T represented by binary index i, V_{f(T)} gives us the valid sizes of intersections
 *   with S. This allows us to prune the search space effectively using bitwise operations.
 * - A depth-first search (DFS) is performed over all possible binary encodings of sets.
 * - At each level of recursion, we compute the intersection constraints and backtrack accordingly.
 *
 * Time Complexity: O(2^n)
 * Space Complexity: O(2^n)
 */

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define cs const
#define re register
#define pb push_back
#define pii pair<int, int>
#define ll long long
#define fi first
#define se second
#define bg begin
cs int RLEN = 1 << 22 | 1;
char ibuf[RLEN], *ib, *ob;
inline char gc() {
  (ib == ob) && (ob = (ib = ibuf) + fread(ibuf, 1, RLEN, stdin));
  return (ib == ob) ? EOF : *ib++;
}
inline int read() {
  char ch = gc();
  int res = 0;
  bool f = 1;
  while (!isdigit(ch))
    f ^= ch == '-', ch = gc();
  while (isdigit(ch))
    res = (res + (res << 2) << 1) + (ch ^ 48), ch = gc();
  return f ? res : -res;
}
inline ll readll() {
  char ch = gc();
  ll res = 0;
  bool f = 1;
  while (!isdigit(ch))
    f ^= ch == '-', ch = gc();
  while (isdigit(ch))
    res = (res + (res << 2) << 1) + (ch ^ 48), ch = gc();
  return f ? res : -res;
}
template <typename tp> inline void chemx(tp &a, tp b) { (a < b) ? (a = b) : 0; }
template <typename tp> inline void chemn(tp &a, tp b) { (a > b) ? (a = b) : 0; }
cs int N = 22, M = (1 << N) | 5;
int f[N][M]; // f[i][j] stores the constraint values for subsets of size 2^i
int n;
vector<int> ans; // Stores result set encodings

// Recursive DFS function to find valid subsets S
void dfs(int s, int i) {
  if (i < n) {
    int x = 1 << (n - i - 1);
    // Compute updated constraints for left child of subtree
    for (int j = 0; j < x; j++)
      f[i + 1][j] = f[i][j] & f[i][j + x];
    dfs(s * 2, i + 1);
    // Compute updated constraints for right child of subtree
    for (int j = 0; j < x; j++)
      f[i + 1][j] = (f[i][j]) & (f[i][j + x] >> 1);
    dfs(s * 2 + 1, i + 1);
  } else {
    // Check if current leaf satisfies the constraints
    if (f[n][0] & 1)
      ans.pb(s);
  }
}

int main() {
#ifdef Stargazer
  freopen("1.in", "r", stdin);
#endif
  n = read();
  f[0][0] = 1; // Initialize root with full valid set
  for (int i = 1; i < (1 << n); i++)
    f[0][i] = read(); // Read binary encodings of V_i
  dfs(0, 0); // Start DFS from root
  cout << ans.size() << '\n';
  for (int x : ans)
    cout << x << "\n"; // Output valid set encodings
}


// https://github.com/VaHiX/CodeForces/