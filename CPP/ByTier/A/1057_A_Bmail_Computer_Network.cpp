// Problem: CF 1057 A - Bmail Computer Network
// https://codeforces.com/contest/1057/problem/A

/*
 * Problem: A. Bmail Computer Network
 * Purpose: Reconstruct the path from router 1 to router n in a tree structure,
 *          where each node (router) is connected to a previous node.
 * 
 * Algorithm: 
 *   - Build a parent array from input, where v[i] represents the parent of node i.
 *   - Start from node n and trace up to root (node 1) using parent links.
 *   - Store the path in reverse order and print it correctly.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> v(n + 1, 0); // v[i] stores the parent of node i
  for (long p = 2; p <= n; p++) {
    scanf("%ld", &v[p]); // read parent of each node from input
  }
  std::vector<long> w; // w will store the path from n to 1
  w.push_back(n); // start with last node
  while (w.back() != 1) { // trace until we reach root
    w.push_back(v[w.back()]); // move to parent
  }
  for (long p = w.size() - 1; p >= 0; p--) {
    printf("%ld ", w[p]); // print path in correct order
  }
  puts("");
}


// https://github.com/VaHiX/codeForces/