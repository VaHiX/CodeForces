// Problem: CF 1709 E - XOR Tree
// https://codeforces.com/contest/1709/problem/E

/*
Algorithm: Tree DFS with XOR properties and set operations
Purpose: Find minimum number of operations to make a tree "good",
         where a tree is good if no simple path has XOR sum 0.

Approach:
- Perform DFS on the tree.
- For each node, maintain a set of XOR values from root to current node.
- When processing children, merge their sets and check if any two XOR values in the set XOR to 0.
- If found, increment operation count (by clearing set to start fresh).
- Time Complexity: O(n * log n) due to set operations
- Space Complexity: O(n) for storage of tree and sets

Key Concepts:
- XOR properties: a ^ a = 0; so if path from root to u has XOR = x, and path from root to v has XOR = x, 
  then path from u to v has XOR = 0.
- DFS traversal with maintaining XOR from root to current node to detect zero paths.
- Use of sets to efficiently check if XOR of any two prefixes equals zero.
*/

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;
const int N = 2e5 + 7;
vector<int> mp[N]; // adjacency list representation of tree
int n, v[N], a[N], ans; // v[i] stores XOR from root to node i; a[i] stores value on node i; ans counts operations
set<int> s[N]; // s[i] stores set of XOR values from root to nodes in subtree of i

void dfs(int x, int fa) {
  int f = 0;
  v[x] = v[fa] ^ a[x]; // XOR from root to current node
  s[x].insert(v[x]); // insert current XOR value into set

  // Traverse children
  for (int i : mp[x])
    if (i != fa) {
      dfs(i, x); // recursive DFS on child

      // Optimization: swap sets to always merge smaller set into larger one
      if (s[i].size() > s[x].size())
        s[i].swap(s[x]);

      // Check if XOR of any two elements from the two sets equals a[x]
      // This means a path exists with XOR = 0
      for (int V : s[i])
        f |= s[x].count(a[x] ^ V);

      // Merge smaller set into larger one
      for (int V : s[i])
        s[x].insert(V);
    }

  // If contradiction detected, we must change value at this node
  if (f)
    ans++, s[x].clear(); // increment operation count and reset set
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 1, x, y; i < n; i++)
    cin >> x >> y, mp[y].push_back(x), mp[x].push_back(y); // build adjacency list
  dfs(1, 0); // start DFS from root node 1 with parent 0
  cout << ans << '\n'; // output result
}


// https://github.com/VaHiX/CodeForces/