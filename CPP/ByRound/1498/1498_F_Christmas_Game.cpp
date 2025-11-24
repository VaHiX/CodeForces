// Problem: CF 1498 F - Christmas Game
// https://codeforces.com/contest/1498/problem/F

/*
Code Purpose:
This code solves the Christmas Game problem where Alice and Bob play a game on a tree of presents.
The game involves moving presents from deeper nodes to ancestors at depth k.
The solution uses a tree DP approach with XOR operations to determine the winning player for each possible root.

Algorithms/Techniques:
- Tree DFS traversal with dynamic programming
- XOR operations for game state calculation (Nim-like game)
- Heavy-light decomposition style processing for subtree operations

Time Complexity: O(n * k)
Space Complexity: O(n * k)
*/
#include <stdio.h>
#include <iosfwd>

#define rep(i, a, b) for (int i = a; i <= b; i++)
#define pre(i, a, b) for (int i = a; i >= b; i--)
#define N 100005
using namespace std;
int h[N], tot, n, k, a[N], ans[N];
struct edge {
  int to, nxt;
} e[N << 1];
void add(int x, int y) {
  e[++tot].nxt = h[x];
  h[x] = tot;
  e[tot].to = y;
}
int f[N][40];
void dfs(int x, int y) {
  f[x][0] ^= a[x]; // Initialize the xor value for current node with its presents
  for (int i = h[x]; i; i = e[i].nxt)
    if (e[i].to != y) {
      dfs(e[i].to, x);
      rep(j, 0, 2 * k - 1) f[x][(j + 1) % (2 * k)] ^= f[e[i].to][j]; // Combine subtree results into parent's state
    }
}
void calc(int x, int fa) {
  rep(i, k, 2 * k - 1) ans[x] ^= f[x][i]; // XOR relevant bits to determine game state for current root
  int g[40];
  for (int i = h[x]; i; i = e[i].nxt)
    if (e[i].to != fa) {
      rep(j, 0, 2 * k - 1) g[(j + 1) % (2 * k)] =
          f[x][(j + 1) % (2 * k)] ^ f[e[i].to][j]; // Compute new state for the child
      rep(j, 0, 2 * k - 1) f[e[i].to][(j + 1) % (2 * k)] ^= g[j]; // Propagate the updated state
      calc(e[i].to, x); // Continue with the child node
    }
}
int main() {
  scanf("%d%d", &n, &k);
  rep(i, 1, n - 1) {
    int x, y;
    scanf("%d%d", &x, &y);
    add(x, y);
    add(y, x);
  }
  rep(i, 1, n) scanf("%d", &a[i]);
  dfs(1, 0); // First DFS to calculate initial states
  calc(1, 0); // Second DFS to compute final results for all roots
  rep(i, 1, n) printf("%d ", ans[i] ? 1 : 0); // Output results
  return 0;
}


// https://github.com/VaHiX/CodeForces/