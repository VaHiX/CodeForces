// Problem: CF 2133 C - The Nether
// https://codeforces.com/contest/2133/problem/C

/*
 * Problem: C. The Nether
 * Purpose: Find the longest path in a directed acyclic graph using interactive queries.
 * Algorithm: 
 *   - Use binary search-like approach to find maximum path length and reconstruct path.
 *   - Query for each node's longest path within subsets of nodes.
 *   - Reconstruct the actual path by backtracking using queries between nodes.
 * Time Complexity: O(n^2) per test case
 * Space Complexity: O(n) per test case
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
const int N = 2e5 + 5;
int n;
vector<int> a[N], res; // a[i] stores nodes that have longest path of length i
void work() {
  scanf("%d", &n);
  string p = ""; // string to hold node indices for query input
  res.clear();
  for (int i = 1; i <= n; i++)
    a[i].clear(), p += to_string(i), p += ' '; // build initial node list

  int mx = 0; // maximum observed path length
  for (int i = 1, t; i <= n; i++) {
    // Query the longest path starting from node i with all nodes as options
    cout << '?' << ' ' << i << ' ' << n << ' ' << p << endl;
    fflush(stdout);
    scanf("%d", &t); 
    a[t].push_back(i); // store node i under its maximum path length
    mx = max(mx, t); // update maximum path length seen so far
  }

  res.push_back(a[mx][0]); // start of the reconstructed longest path

  // Backtrack to build full path from the node that gave max length
  for (int i = mx - 1; i; i--) {
    int t = res.back(), p;
    for (auto j : a[i]) {
      // Ask if we can reach j starting from last node in path with only two nodes
      cout << '?' << ' ' << t << ' ' << 2 << ' ' << t << ' ' << j << endl;
      fflush(stdout);
      scanf("%d", &p);
      if (p != 1) { // if we can't reach j, this is a valid next node in path
        res.push_back(j);
        break;
      }
    }
  }

  // Output solution: max length and the nodes in the longest path
  printf("! %d ", mx);
  for (auto i : res)
    printf("%d ", i);
  cout << endl, fflush(stdout);
}
int main() {
  int t;
  scanf("%d", &t);
  while (t--)
    work();
  return 0;
}


// https://github.com/VaHiX/codeForces/