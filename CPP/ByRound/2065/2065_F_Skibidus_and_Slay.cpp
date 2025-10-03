// Problem: CF 2065 F - Skibidus and Slay
// https://codeforces.com/contest/2065/problem/F

/*
F. Skibidus and Slay
Algorithms/Techniques: Tree DFS, Majority Voting, Path Analysis

Time Complexity: O(n) per test case amortized due to each edge being processed at most twice across all vertices.
Space Complexity: O(n) for storing the tree and auxiliary arrays.

The problem asks us to determine for each vertex whether there exists a non-trivial path in which that vertex's value is the majority.
Majority is defined as appearing strictly more than floor(k/2) times in a sequence of k elements.
We use a DFS traversal with frequency counting on adjacent node values to detect if any value can be majority along any valid path.
*/

#include <stdio.h>
#include <vector>
using namespace std;

int n, a[500005], b[500005], ans[500005];
vector<int> edge[500005];

void solve() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    edge[i].clear(), ans[i] = 0;
  }
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    if (a[u] == a[v])
      ans[a[u]] = 1; // If two adjacent nodes have same value, it's possible to form a path with that majority
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    for (auto j : edge[i]) {
      if (b[a[j]])
        ans[a[j]] = 1; // If value a[j] has been seen before, there is potential to form majority path
      b[a[j]]++; // Increment count of value a[j]
    }
    for (auto j : edge[i])
      b[a[j]]--; // Decrement count after processing this neighbor
  }
  for (int i = 1; i <= n; i++)
    printf("%d", ans[i]);
  putchar('\n');
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--)
    solve();
}


// https://github.com/VaHiX/codeForces/