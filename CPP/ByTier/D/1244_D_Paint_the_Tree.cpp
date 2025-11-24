// Problem: CF 1244 D - Paint the Tree
// https://codeforces.com/contest/1244/problem/D

/*
D. Paint the Tree
Algorithms/Techniques: DFS traversal, brute-force permutation, tree properties
Time Complexity: O(3! * n) = O(n), since 3! = 6 is constant and we traverse the tree once
Space Complexity: O(n), for storing the tree structure and auxiliary arrays

This code solves the problem of painting a tree with three colors such that 
no path of exactly three distinct vertices has all vertices with the same color.
The solution uses DFS to process the tree in a linear fashion (since the graph is a tree),
and tries all permutations of coloring for nodes in the path, keeping track of minimum cost.

The key idea:
1. If any node has degree >= 3, then it's impossible to avoid conflict -> return -1
2. If the tree is a line, we can greedily assign colors or try permutations and pick minimum one
*/
#include <stdio.h>
#include <algorithm>
#include <vector>

#define pb push_back
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
bool ok;
int n, num[3], rt, c[3][N], u, v;
vector<int> E[N], f;
int ans[N];

// DFS traversal to collect path from root
void dfs(int x, int fa) {
  f.pb(x);
  for (int v : E[x]) {
    if (v == fa)
      continue;
    dfs(v, x);
  }
}

// Try all permutations of colors and compute minimum cost
ll solve(int x) {
  f.pb(0); // padding to make indexing easier
  dfs(x, -1);
  for (int i = 0; i < 3; ++i)
    num[i] = i;
  ll res = 8e18;
  do {
    ll tmp = 0;
    for (int i = 1; i <= n; ++i)
      tmp += c[num[i % 3]][f[i]]; // assign color based on permutation and accumulate cost
    if (res > tmp) {
      res = tmp;
      for (int i = 1; i <= n; ++i)
        ans[f[i]] = num[i % 3]; // save optimal assignment
    }
  } while (next_permutation(num, num + 3)); // check all 3! color permutations
  return res;
}

int main() {
  scanf("%d", &n);
  for (int j = 0; j < 3; ++j) { // read cost matrix for colors
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &c[j][i]);
    }
  }
  for (int i = 1; i < n; ++i) { // build adjacency list from edges
    scanf("%d%d", &u, &v);
    E[u].pb(v), E[v].pb(u);
  }
  for (int i = 1; i <= n; ++i) {
    if (E[i].size() >= 3) { // check if there's a vertex with degree >= 3
      ok = 1;
      break;
    }
    if (E[i].size() == 1)
      rt = i; // find leaf as root for linear traversal
  }
  if (ok)
    puts("-1"); // impossible case
  else {
    printf("%I64d\n", solve(rt)); // compute minimum cost
    for (int i = 1; i <= n; ++i)
      printf("%d%c", 1 + ans[i], " \n"[i == n]); // output color assignments
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/