// Problem: CF 1671 E - Preorder
// https://codeforces.com/contest/1671/problem/E
 
/*
Purpose: 
  This code calculates the number of different preorder strings that can be obtained from a perfect binary tree 
  by swapping children of non-leaf vertices any number of times. 
  It uses a depth-first search (DFS) to traverse the tree, and for each node, determines whether swapping 
  its children affects the final count of distinct preorder strings.
 
Algorithms/Techniques:
  - DFS traversal of a perfect binary tree represented as an array.
  - Dynamic counting of possibilities using a modular arithmetic approach.
  - Comparison and swapping of left and right subtree preorder strings to determine equivalence.
 
Time Complexity: O(2^n)
  - The tree has 2^n - 1 nodes, and we visit each node once during DFS traversal.
Space Complexity: O(2^n)
  - The recursion stack depth is O(n), and the string operations contribute to space usage proportional to the number of nodes.
*/
 
#include <iostream>
#include <string>
 
#define int long long
using namespace std;
const int mod = 998244353;
string s;
int ans;
string dfs(int u) {
  // If current node is a leaf (no children), return its character
  if (u * 2 + 1 >= s.size()) {
    return (string) "" + s[u];
  }
  // Recursively compute preorder strings for left and right children
  string x = dfs(u * 2 + 1);
  string y = dfs(u * 2 + 2);
  // If left and right preorder strings are different, we have a choice to swap
  if (x != y)
    ans = ans * 2 % mod;
  // Ensure x >= y for consistent ordering (used for comparison later)
  if (x < y)
    swap(x, y);
  // Return the preorder string for this node: node_char + left_subtree + right_subtree
  return (string) "" + s[u] + x + y;
}
signed main() {
  int n;
  cin >> n;
  cin >> s;
  ans = 1;
  dfs(0);
  cout << ans << endl;
}
 
 
// https://github.com/VaHiX/CodeForces/