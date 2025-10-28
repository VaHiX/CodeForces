// Problem: CF 2002 D1 - DFS Checker (Easy Version)
// https://codeforces.com/contest/2002/problem/D1

/*
 * Purpose: Determines if a given permutation of vertices of a perfect binary tree
 *          represents a valid DFS traversal order after a series of swaps.
 *
 * Algorithm:
 *   - Build a perfect binary tree with n nodes (n = 2^k - 1)
 *   - For each query:
 *     - Swap two elements in the permutation
 *     - Check if the resulting permutation is a valid DFS order
 *   - Uses a bottom-up approach with recursive DFS check on the tree
 *   - Maintains a global "ok" array to track valid DFS orders for each subtree
 *   - Uses a "rev" array to map vertex values to their positions in the permutation
 *   - Uses "sz" array to store size of each subtree to determine valid child order
 *
 * Time Complexity: O(n log n + q * log n)
 *   - O(n) to initialize tree information
 *   - O(log n) per query for DFS validation (upward propagation)
 * 
 * Space Complexity: O(n)
 *   - Stores arrays for tree structure and validation info
 */
#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using uint = unsigned int;
using db = double;
int n;
vector<bool> ok;        // Tracks if subtree rooted at i is valid DFS order
vector<int> sz, rev, p;  // sz: subtree sizes, rev: reverse mapping of permutation, p: current permutation

// Initialize the valid DFS status for each node
void initdfs(int v) {
  if (v * 2 >= n) {     // Base case: leaf node
    ok[v] = true;
    return;
  }
  initdfs(2 * v);       // Recursively process left child
  initdfs(2 * v + 1);   // Recursively process right child
  
  // If either child is invalid, then current node is also invalid
  if (!ok[2 * v] || !ok[2 * v + 1]) {
    ok[v] = false;
    return;
  }
  
  // Check if the current node follows valid DFS order based on children
  // Case 1: Left child comes first
  if ((rev[v] + 1 == rev[2 * v]) &&
      (rev[v] + 1 + sz[2 * v] == rev[2 * v + 1])) {
    ok[v] = true;
    return;
  }
  // Case 2: Right child comes first
  if ((rev[v] + 1 == rev[2 * v + 1]) &&
      (rev[v] + 1 + sz[2 * v + 1] == rev[2 * v])) {
    ok[v] = true;
    return;
  }
  ok[v] = false;        // Neither case holds, invalid DFS
}

// Update the DFS validity for all ancestral nodes after a swap
void upd(int a, int b) {
  if (a < b) {
    swap(a, b);         // Ensure a >= b
  }
  if (a == b) {
    b /= 2;             // Handle case where a == b (special handling)
  }
  if (a == 0) {
    return;             // Base case reached
  }
  if (a * 2 >= n) {
    upd(a / 2, b);      // If a is leaf, update parent
    return;
  }
  
  // If either child is invalid, current node is also invalid
  if (!ok[2 * a] || !ok[2 * a + 1]) {
    ok[a] = false;
    upd(a / 2, b);
    return;
  }
  
  // Check if DFS order is valid based on children placement
  if ((rev[a] + 1 == rev[2 * a]) &&
      (rev[a] + 1 + sz[2 * a] == rev[2 * a + 1])) {
    ok[a] = true;
    upd(a / 2, b);
    return;
  }
  if ((rev[a] + 1 == rev[2 * a + 1]) &&
      (rev[a] + 1 + sz[2 * a + 1] == rev[2 * a])) {
    ok[a] = true;
    upd(a / 2, b);
    return;
  }
  ok[a] = false;
  upd(a / 2, b);
}

// Process each test case
void sol() {
  int q, a, b;
  cin >> n >> q;
  sz.resize(n + 1), ok.resize(n + 1), rev.resize(n + 1), p.resize(n + 1);
  
  int cur = n, st = 2;  // st tracks boundary of current level in the tree
  for (int i = 1; i <= n; i++) {
    if (i == st) {
      cur /= 2;         // When we reach the end of a level, decrease level size
      st *= 2;
    }
    sz[i] = cur;        // Fill subtree sizes
  }
  
  // Read parent information (not used in code as it's confirmed to be floor(i/2))
  for (int i = 0; i < n - 1; i++) {
    cin >> a;
  }
  
  // Initialize permutation and reverse mapping
  for (int i = 1; i <= n; i++) {
    cin >> p[i];
    rev[p[i]] = i;      // Map vertex value to its index in permutation
  }
  
  initdfs(1);           // Start initialization from root
  
  // Process queries
  for (int i = 0; i < q; i++) {
    cin >> a >> b;
    swap(p[a], p[b]);   // Swap values in permutation
    rev[p[a]] = a;      // Update reverse mapping
    rev[p[b]] = b;
    upd(p[a], p[b]);    // Update validity of affected nodes
    if (ok[1]) {        // Print result for root
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--) {
    sol();
  }
}


// https://github.com/VaHiX/CodeForces/