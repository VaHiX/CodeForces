// Problem: CF 1988 D - The Omnipotent Monster Killer
// https://codeforces.com/contest/1988/problem/D

/*
D. The Omnipotent Monster Killer

Algorithms/Techniques: Tree Dynamic Programming with Binary Lifting / Path-based optimization, DFS traversal.

Time Complexity: O(n * log n) per test case due to the use of DFS and maintaining prefix minimums for each node in a tree structure.
Space Complexity: O(n * 24) for storing dp states f[x][i] and smn array for each node.

This problem models an optimal selection of monsters to kill on a tree such that in every round:
- All current monsters attack (sum of their attacks)
- You choose which monsters to kill (non-adjacent ones)
- Goal is to minimize total health loss over many rounds

We use a post-order DFS to compute for each node the minimum cost of selecting some subset of monsters
in its subtree, subject to no two adjacent monsters being selected.
*/
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
int n;
long long a[300005], f[300005][24], smn[30]; // f stores dp values, smn helps track prefix minima
vector<int> g[300005];

void dfs(int x, int fa) {
  // Initialize f[x][i] with i * a[x]
  for (int i = 1; i <= 22; i++)
    f[x][i] = i * a[x];
  
  // Traverse children
  for (int y : g[x]) {
    if (y == fa) continue; // Skip parent
    
    dfs(y, x); // Recursively process child
    
    long long tt = 8e18;
    smn[23] = 8e18;
    
    // Precompute suffix minimums
    for (int i = 22; i >= 1; i--)
      smn[i] = min(smn[i + 1], f[y][i]);
      
    // Update dp values based on child's results
    for (int i = 1; i <= 22; i++) {
      f[x][i] += min(tt, smn[i + 1]); // Add best valid choice from child
      tt = min(tt, f[y][i]); // Maintain minimum so far
    }
  }
}

void Solve() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  
  dfs(1, 0); // Start DFS from node 1
  
  cout << *min_element(f[1] + 1, f[1] + 23) << '\n';
  
  // Clean up for next test case
  for (int i = 1; i <= n; i++) {
    g[i].clear();
    memset(f[i], 0, sizeof(f[i]));
  }
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int t;
  cin >> t;
  while (t--)
    Solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/