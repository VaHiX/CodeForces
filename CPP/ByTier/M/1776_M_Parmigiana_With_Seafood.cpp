// Problem: CF 1776 M - Parmigiana With Seafood
// https://codeforces.com/contest/1776/problem/M

/*
Problem: Game on Tree - Optimal Play for Maximum Label in Recipe
Algorithms/Techniques: Tree DFS, Game Theory, Optimal Strategy
Time Complexity: O(n)
Space Complexity: O(n)

The problem models a two-player game on a tree where players alternate removing leaf nodes,
with Alessandro (first) adding to the recipe and Bianca (second) discarding. 
Alessandro wants to maximize the maximum label in the recipe, while Bianca wants to minimize it.
This is solved by analyzing optimal play using depth and parent tracking.
*/

#include <iostream>

using namespace std;
const int N = 1e5 + 5;
int n, head[N], d[N], tot, dep[N], fa[N], cnt[N];
bool vis[N];
struct o {
  int ne, to;
} e[N << 1];
inline void add(int x, int y) {
  e[++tot].ne = head[x];   // Add edge from x to y
  head[x] = tot;
  e[tot].to = y;
}
inline void dfs(int x, int f) {
  fa[x] = f, dep[x] = dep[f] ^ 1;  // Set parent and depth parity
  for (int i = head[x]; i; i = e[i].ne) {  // Traverse neighbors
    int to = e[i].to;
    if (to == f)
      continue;
    dfs(to, x);
  }
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> n;
  if (!(n & 1)) {  // If n is even, Alessandro wins by taking last move
    cout << n;
    return 0;
  }
  for (int i = 1; i < n; i++) {  // Read edges and build tree
    int x, y;
    cin >> x >> y;
    d[x]++, d[y]++;   // Increment degree
    add(x, y), add(y, x);  // Add bidirectional edge
  }
  dep[0] = 1;   // Root depth is set to 1
  dfs(n, 0);   // DFS from node n to compute depths and parents
  for (int i = n; i; i--) {  // Iterate from n down to 1
    if (d[i] == 1 || dep[i] == 1) {  // If leaf or depth is 1
      cout << i;
      return 0;
    }
    int x = i;
    while (!vis[x])   // Traverse path up to root, mark visited
      vis[x] = 1, x = fa[x], cnt[x]++;
    if ((x != n && cnt[x] >= 2 && !dep[x]) || (x == n && cnt[x] >= 3)) {  // Check for optimal node
      cout << i;
      return 0;
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/