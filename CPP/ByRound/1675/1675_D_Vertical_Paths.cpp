// Problem: CF 1675 D - Vertical Paths
// https://codeforces.com/contest/1675/problem/D
 
/*
Code Purpose:
This code solves the problem of finding the minimum number of downward paths in a rooted tree such that all vertices are covered exactly once. 
Each path must go from a parent to its children (downward direction).
The solution involves:
1. Identifying the root(s) of the tree (vertices where p[i] == i)
2. Using a DFS approach to traverse and form paths
3. Counting the minimum number of paths needed (equal to number of leaves or end vertices in tree structure)
4. For each root, performing DFS and printing the paths
 
Algorithms/Techniques:
- DFS traversal to explore tree structure
- Root identification and path building
- Tracking visited nodes and parent-child relationships
 
Time Complexity:
O(n) - Each node is visited once during DFS traversal.
 
Space Complexity:
O(n) - Storage for arrays to track parent relationships, visited nodes, and path information.
*/
 
#include <string.h>
#include <iostream>
 
using namespace std;
int t, n, p[200001], v[200001];  // p: parent array; v: visited array
int a[200005];  // a: count of children for each node
 
void dfs(int x, int father) {
  v[x] = 1;  // Mark current node as visited
  if (x != p[x] && !v[p[x]])  // If current node is not root and parent is not visited
    dfs(p[x], father + 1);  // Continue DFS on the parent
  else  // If parent is visited or current node is root
    cout << father << endl;  // Print the length of the path
  cout << x << ' ';  // Print the current vertex
}
 
int main() {
  cin >> t;
  while (t--) {  // For each test case
    cin >> n;
    int cnt = n;  // Initialize count of paths as total number of nodes
    for (int i = 1; i <= n; i++) {  // For each node
      cin >> p[i];  // Read parent
      if (i != p[i])  // If node is not root
        cnt -= !a[p[i]]++;  // Increment count of children for parent
    }
    cout << cnt << endl;  // Print minimum number of paths
    for (int i = 1; i <= n; i++)  // For each node
      if (a[i] == 0)  // If node has no children (leaf or root)
        dfs(i, 1), cout << endl;  // Start DFS from this node
    memset(a, 0, sizeof a);  // Reset array a
    memset(v, 0, sizeof v);  // Reset array v
    cout << endl;  // Print newline after each test case
  }
}
 
 
// https://github.com/VaHiX/CodeForces/