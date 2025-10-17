// Problem: CF 2013 F1 - Game in Tree (Easy Version)
// https://codeforces.com/contest/2013/problem/F1

/*
F1. Game in Tree (Easy Version)
Algorithms/Techniques: Tree DFS, LCA preprocessing, game theory on trees
Time Complexity: O(n) per test case amortized
Space Complexity: O(n)

This problem involves a two-player game played on a tree where players move from their starting positions to unvisited neighbors.
Alice starts at vertex 1 and Bob starts at different vertices along the path from u to v.
The goal is to determine the winner of the game for each position Bob can take.
*/
#include <algorithm>
#include <iostream>
#define maxn 200010
using namespace std;
struct edge {
  int pre, to;
#define pre(i) ed[i].pre
#define to(i) ed[i].to
} ed[2 * maxn];
int cnt, head[maxn];
void merge(int a, int b) {
  ++cnt;
  pre(cnt) = head[a];
  to(cnt) = b;
  head[a] = cnt;
}
int T, n, u, v, fa[maxn], dep[maxn], mdep[maxn], ans[maxn], LCA;
void dfs(int x, int f) {
  fa[x] = f;
  dep[x] = dep[f] + 1;
  mdep[x] = dep[x];
  for (int i = head[x]; i; i = pre(i)) {
    int l = to(i);
    if (l == f)
      continue;
    dfs(l, x);
    mdep[x] = max(mdep[x], mdep[l]);
  }
}
int q[maxn], ct, A[maxn], B[maxn];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1, a, b; i < n; ++i) {
      cin >> a >> b;
      merge(a, b);
      merge(b, a);
    }
    dfs(1, 0); // Precompute father and depth
    cin >> u >> v;
    int pre = 0, now = u, flag = 0;
    ct = 0;
    while (now) {
      q[++ct] = now; // Store path from u to v
      for (int i = head[now]; i; i = pre(i)) {
        int l = to(i);
        if (l == pre || l == fa[now])
          continue;
        ans[now] = max(ans[now], mdep[l] - dep[now]); // Compute max depth of subtree
      }
      pre = now;
      now = fa[now];
    }
    int N = (ct + 1) / 2; // Middle point of the path
    for (int i = N; i < ct; ++i) {
      int l = i, r = 2 * N - i;
      if (ct % 2 == 1)
        r--;
      B[l] =
          max(dep[u] - dep[q[l]] + ans[q[l]], dep[u] - dep[q[r]] + ans[q[r]]);
      if (l > N)
        B[l] = max(B[l], B[l - 1]);
    }
    for (int i = N; i > 1; --i) {
      int l = i, r = 2 * N - i;
      if (ct % 2 == 0)
        r++;
      A[l] = max(dep[q[l]] - 1 + ans[q[l]], dep[q[r]] - 1 + ans[q[r]]);
      if (l < N)
        A[l] = max(A[l], A[l + 1]);
    }
    int L = ct, R = 1;
    while (1) {
      // Game simulation: Alice has a move, but Bob might force a win
      if (dep[q[L]] - 1 + ans[q[L]] > B[L - 1]) { // Critical condition for Alice
        flag = 1;
        break;
      } else if (L - 1 <= R) {
        flag = 0;
        break;
      } else
        L--;
      if (dep[u] - dep[q[R]] + ans[q[R]] >= A[R + 1]) {
        flag = 0;
        break;
      } else if (R + 1 >= L) {
        flag = 1;
        break;
      } else
        R++;
    }
    if (!flag)
      cout << "Bob" << endl;
    else
      cout << "Alice" << endl;
    for (int i = 1; i <= n; ++i)
      ans[i] = head[i] = 0;
    cnt = 0;
  }
}


// https://github.com/VaHiX/codeForces/