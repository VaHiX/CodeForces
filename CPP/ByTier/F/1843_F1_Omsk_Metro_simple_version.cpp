// Problem: CF 1843 F1 - Omsk Metro (simple version)
// https://codeforces.com/contest/1843/problem/F1

/*
Code Purpose:
This solution handles queries for a tree-based metro system where each node has a weight of -1 or 1.
The task is to determine if there exists a subpath between two nodes such that the sum of weights equals a given value k.
The algorithm uses dynamic programming to track the maximum and minimum prefix sums from the root (node 1) to each node,
allowing for efficient range queries over the path between any two nodes.

Approaches/Techniques:
- Tree traversal with dynamic programming
- Path sum query using prefix sums
- Efficient precomputation for queries

Time Complexity:
- Preprocessing: O(n) for n operations
- Each query: O(1) after preprocessing
- Total: O(n) for all operations combined

Space Complexity:
- O(n) for storing the tree and DP arrays
*/

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
#define mp make_pair
#define pb push_back
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> weight = {1}; // Initial weight of the only station (node 1)
    vector<int> mx = {1};     // Maximum prefix sum from root to current node
    vector<int> mn = {0};     // Minimum prefix sum from root to current node
    vector<int> dp_mx = {1};  // Maximum subarray sum ending at current node
    vector<int> dp_mn = {0};  // Minimum subarray sum ending at current node
    for (int i = 0; i < n; i++) {
      char c;
      cin >> c;
      if (c == '+') {
        int v, x;
        cin >> v >> x;
        v--; // Convert to 0-based index
        weight.pb(x); // Add new weight to the vector
        dp_mx.pb(max(dp_mx[v] + x, 0)); // Compute max subarray sum ending at new node
        dp_mn.pb(min(dp_mn[v] + x, 0)); // Compute min subarray sum ending at new node
        mx.pb(max(mx[v], dp_mx[dp_mx.size() - 1])); // Update global max prefix sum
        mn.pb(min(mn[v], dp_mn[dp_mn.size() - 1])); // Update global min prefix sum
      } else {
        int u, v, k;
        cin >> u >> v >> k;
        v--; // Convert to 0-based index
        // Check if k is within the range of possible path sums
        if (k <= mx[v] && k >= mn[v]) {
          cout << "YES\n";
        } else {
          cout << "NO\n";
        }
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/