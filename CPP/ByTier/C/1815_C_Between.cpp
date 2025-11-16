// Problem: CF 1815 C - Between
// https://codeforces.com/contest/1815/problem/C

/*
Algorithm/Techniques: 
- Graph traversal using BFS to determine connectivity and build a tree structure.
- For each node, we track its level in BFS tree to decide how many times it should appear in the constructed sequence.
- Construction of the sequence by layering elements from BFS levels, ensuring that the constraints are satisfied.

Time Complexity:
- O(n + m) per test case for BFS traversal and processing.
- Total time complexity over all test cases is bounded by the given constraints.

Space Complexity:
- O(n + m) for storing adjacency list and auxiliary arrays.
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#define pb push_back
using namespace std;
vector<int> e[1510], t[1510]; // e: adjacency list for reverse graph, t: levels of BFS tree
int bfsn[1510], vis[1510];    // bfsn: level of each node in BFS, vis: visited flag

// BFS to build a tree structure rooted at node 1
void bfs() {
  queue<int> q;
  q.push(1);
  bfsn[1] = 1;
  vis[1] = 1;
  t[1].pb(1); // Root node at level 1
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : e[u]) {
      if (vis[v])
        continue;
      vis[v] = 1;
      bfsn[v] = bfsn[u] + 1;
      t[bfsn[v]].pb(v);
      q.push(v);
    }
  }
}

void solve() {
  int n, m;
  cin >> n >> m;
  // Clear all data structures
  for (int i = 1; i <= n; i++)
    e[i].clear(), t[i].clear(), bfsn[i] = vis[i] = 0;
    
  // Build reverse adjacency list (we process input as b -> a)
  for (int i = 1, a, b; i <= m; i++) {
    cin >> a >> b;
    e[b].pb(a);
  }

  // Special case: only one element
  if (n == 1) {
    cout << "FINITE" << '\n';
    cout << '1' << '\n' << '1' << '\n';
    return;
  }

  bfs();

  // Check if all nodes are reachable from 1
  for (int i = 1; i <= n; i++)
    if (!vis[i]) {
      cout << "INFINITE" << '\n';
      return;
    }

  cout << "FINITE" << '\n';
  int ans = 1; // Start with 1 in sequence
  // Calculate total length of sequence based on level counts
  for (int i = 2; i <= n; i++) {
    ans += ((int)t[i].size() * i);
  }
  cout << ans << '\n';
  
  // Construct sequence layer by layer, from higher level to lower
  for (int i = 1; i <= n; i++) {
    for (int j = n; j >= i; j--) {
      for (auto v : t[j])
        cout << v << ' ';
    }
  }
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int T = 1;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/