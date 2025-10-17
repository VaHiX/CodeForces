// Problem: CF 2118 F - Shifts and Swaps
// https://codeforces.com/contest/2118/problem/F

/*
F. Shifts and Swaps
time limit per test6 seconds
memory limit per test512 megabytes

Algorithms/Techniques: 
- Graph representation of array structure based on element positions
- Tree canonical form using DFS and hashing with rotation detection
- Cyclic shift equivalence handling via rotation
- Canonical string comparison for tree structures

Time Complexity:
O(n * m) average case, O(n * m * log(n)) worst case due to sorting and map operations.

Space Complexity:
O(n * m) for storing the graph structure and canonical representation of trees.
*/

#include <stdio.h>
#include <algorithm>
#include <map>
#include <utility>
#include <vector>

using namespace std;
int n, m, hid;
map<pair<int, vector<int>>, int> mp; // Hash map to store canonical forms of trees
vector<int> get_graph(vector<int> arr) {
  vector<vector<int>> g(n); // Adjacency list for the graph built from array
  vector<int> roots;        // List of root nodes (elements with value 1)
  vector<int> las(m + 1);   // Last occurrence index of each element, with offset to avoid conflict
  for (int i = 0; i < n; i++)
    las[arr[i]] = i;
  for (int i = 0; i < n; i++) {
    if (arr[i] == 1) { // If current element is 1, it's a root node
      roots.push_back(i);
    } else {
      int l = max(las[arr[i] - 1], las[arr[i]]); // Determine parent index based on last appearances
      g[l % n].push_back(i);                     // Add child to graph
    }
    las[arr[i]] = i + n; // Update last appearance with offset for next iteration to avoid clash
  }
  vector<int> sec; // Stores canonical representation of tree
  auto get_mp = [&](auto self, int x) -> int {
    vector<int> ch; // Collect children identifiers
    for (auto e : g[x])
      ch.push_back(self(self, e)); // Recursive call to get identifiers of children
    sort(ch.begin(), ch.end());   // Sort children to make structure canonical
    auto &v = mp[{arr[x], ch}];   // Get or assign identifier for this node's subtree
    if (v == 0)
      v = ++hid; // Assign new identifier if not present
    return v;
  };
  for (auto e : roots) {
    sec.push_back(get_mp(get_mp, e)); // Build canonical representation of the tree rooted at each root
  }
  int k = 0, i = 0, j = 1, n = sec.size(); // KMP-like algorithm to find minimal rotation
  while (k < n && i < n && j < n) {
    if (sec[(i + k) % n] == sec[(j + k) % n]) {
      k++;
    } else {
      sec[(i + k) % n] > sec[(j + k) % n] ? i = i + k + 1 : j = j + k + 1; // Determine which pointer to advance
      if (i == j)
        i++;
      k = 0;
    }
  }
  i = min(i, j); // Find minimal rotation
  rotate(sec.begin(), sec.begin() + i, sec.end()); // Apply rotation
  return sec;
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    hid = 0;
    mp.clear();
    scanf("%d%d", &n, &m);
    vector<int> a, b;
    for (int i = 0, x; i < n; i++)
      scanf("%d", &x), a.push_back(x);
    for (int i = 0, x; i < n; i++)
      scanf("%d", &x), b.push_back(x);
    vector<int> A = get_graph(a), B = get_graph(b); // Get canonical forms
    if (A == B)
      puts("YES");
    else
      puts("NO");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/