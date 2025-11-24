// Problem: CF 1914 F - Programming Competition
// https://codeforces.com/contest/1914/problem/F

/*
------------------------------------------------------------
Problem: F. Programming Competition
Algorithm: Tree DP with greedy approach to maximize team pairs
Time Complexity: O(n) per test case, where n is the number of employees
Space Complexity: O(n) for storing tree structure and subtree sizes

Approach:
- Build a tree from the input where each node represents an employee and edges represent the superior-subordinate relationship.
- Perform DFS to compute the size of each subtree (sz[v] = number of nodes in subtree rooted at v).
- Use a greedy approach in the calc function:
  - For each node, determine how many pairs can be formed in its subtree.
  - Use a greedy strategy to pair nodes while respecting the constraint that one cannot be a superior of another.
  - The solution uses a recursive approach with memoization-like logic to compute the maximum number of valid pairs.
------------------------------------------------------------
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int N = 222222;
int n;
int sz[N]; // sz[v] stores the size of subtree rooted at v
vector<int> g[N]; // g[v] stores the list of children of node v

// Initialize the subtree sizes by DFS traversal
void init(int v) {
  sz[v] = 1; // Every node has size 1 initially
  for (int u : g[v]) { // For each child u of v
    init(u); // Recursively initialize subtree of u
    sz[v] += sz[u]; // Add the size of u's subtree to v's subtree
  }
}

// Calculate the maximum number of valid teams that can be formed in the subtree rooted at v
// k represents the number of nodes already paired or used from parent's subtree
int calc(int v, int k) {
  int tot = 0, mx = -1; // tot = total nodes in children subtrees, mx = child with maximum subtree size
  for (int u : g[v]) { // For each child u of v
    tot += sz[u]; // Add size of u's subtree to total
    if (mx == -1 || sz[mx] < sz[u]) // Update the child with maximum subtree
      mx = u;
  }
  if (tot == 0) // No children
    return 0;
  if (sz[mx] - k <= tot - sz[mx]) // Greedy decision based on subtree sizes
    return (tot - k) / 2;
  int add = tot - sz[mx]; // Additional pairs from non-maximal subtrees
  return add + calc(mx, max(0, k + add - 1)); // Recursively process the maximal subtree
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 0; i < n; ++i)
      g[i].clear(); // Clear the adjacency list for current test case
    for (int i = 1; i < n; ++i) {
      int p;
      cin >> p;
      g[p - 1].push_back(i); // Add i as a child of p (0-indexed)
    }
    init(0); // Initialize subtree sizes starting from root (0)
    cout << calc(0, 0) << '\n'; // Calculate and print the answer for this test case
  }
}


// https://github.com/VaHiX/CodeForces/