// Problem: CF 1824 C - LuoTianyi and XOR-Tree
// https://codeforces.com/contest/1824/problem/C

/*
Purpose: Solve the problem of making all root-to-leaf paths in a tree have XOR value zero with minimum operations.

Algorithm:
- This problem exploits the property of XOR and uses a tree DFS approach combined with frequency counting.
- For each node, we track the XOR values from the root to that node using a map.
- During DFS traversal, we merge child maps into the parent's map to find how many paths already match.
- The minimum operations for a subtree equals the number of children minus the maximum frequency of a matching XOR value.
- After processing all children, we keep only those XOR values that appear the maximum number of times to ensure optimal merging.

Time Complexity: O(n log n)
Space Complexity: O(n log n)

Techniques:
- Tree DFS
- Map-based frequency counting
- XOR property: x ^ x = 0
*/

#include <stdio.h>
#include <algorithm>
#include <map>
#include <utility>
#include <vector>

#define fp(i, a, b) for (int i = a, i##_ = int(b); i <= i##_; ++i)
#define fd(i, a, b) for (int i = a, i##_ = int(b); i >= i##_; --i)
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
int n, a[N], ans;
vector<int> G[N];
map<int, int> S[N];
void dfs(int u, int fa) {
  int mx_appr = 1, ch = 0;
  for (auto x : G[u])
    if (x != fa) {
      a[x] ^= a[u], dfs(x, u), ++ch;
      if (S[x].size() > S[u].size())
        swap(S[x], S[u]);
      for (auto [a, b] : S[x])
        mx_appr = max(mx_appr, S[u][a] += b);
      S[x].clear();
    }
  if (!ch)
    S[u][a[u]] = 1;
  else
    ans += ch - mx_appr;
  if (mx_appr != 1) {
    map<int, int> temp;
    for (auto [x, y] : S[u])
      if (y == mx_appr)
        temp[x] = 1;
    S[u].swap(temp);
  }
}
void Solve() {
  scanf("%d", &n);
  fp(i, 1, n) scanf("%d", a + i);
  for (int i = 1, u, v; i < n; ++i) {
    scanf("%d%d", &u, &v);
    G[u].push_back(v), G[v].push_back(u);
  }
  dfs(1, 1);
  printf("%d\n", ans + (!S[1].count(0)));
}
int main() {
  int t = 1;
  while (t--)
    Solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/