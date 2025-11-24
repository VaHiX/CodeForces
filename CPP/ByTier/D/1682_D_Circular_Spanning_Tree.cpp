// Problem: CF 1682 D - Circular Spanning Tree
// https://codeforces.com/contest/1682/problem/D

/*
 * Problem: D. Circular Spanning Tree
 * 
 * Purpose: This code constructs a spanning tree on nodes arranged in a circle such that:
 *          - Each node has even degree if s[i] = 0, odd degree if s[i] = 1
 *          - No two edges intersect internally in the circle
 * 
 * Algorithm:
 *   1. Validate feasibility: 
 *      - Sum of s must be even (degree constraint for tree)
 *      - At least one node must have s[i] = 1 (to avoid trivial case)
 *   2. Build the tree:
 *      - For all nodes i where s[i+1] = 1, store indices in array a
 *      - For all nodes i where s[i+1] = 0, connect i to (i % n) + 1
 *      - Connect all stored nodes to the first one in array a
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the array and string
 */
#include <iostream>

using namespace std;
#define int long long
int t, n, a[200010], len = 0;
char c[200010];
signed main() {
  cin >> t;
  while (t--) {
    cin >> n;
    len = 0;
    int flg = 0, cnt = 0;
    for (int i = 1; i <= n; i++)
      cin >> c[i], c[i] -= '0', flg ^= c[i], cnt += c[i]; // Read string and compute parity and count of 1s
    
    // If total number of 1s is odd or zero, it's impossible to satisfy degree constraints
    if (flg || cnt == 0) {
      cout << "NO" << endl;
      continue;
    }
    cout << "YES" << endl;
    
    // Make the string circular by duplicating first element at the end
    c[n + 1] = c[1];
    
    // Process each node to build tree
    for (int i = 1; i <= n; i++) {
      if (c[i + 1]) // if next node is 1 (odd degree node)
        a[++len] = i; // add to list of such nodes
      else // if next node is 0 (even degree node)
        cout << i << " " << i % n + 1 << "\n"; // connect to the next node in circle
    }
    
    // Connect all odd degree nodes to the first one
    for (int i = 2; i <= len; i++)
      cout << a[1] << " " << a[i] << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/