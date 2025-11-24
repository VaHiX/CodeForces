// Problem: CF 1889 B - Doremy's Connecting Plan
// https://codeforces.com/contest/1889/problem/B

/*
 * Code Purpose: 
 *   Determine if a graph can be made connected by adding edges between nodes,
 *   where an edge between node i and j is valid if the sum of people in their 
 *   connected component is at least i * j * c. 
 * 
 * Algorithm: 
 *   Greedily connect nodes to the first node (1) by checking if adding a node
 *   to the component of node 1 increases the total population enough to satisfy 
 *   the constraint for future edges.
 * 
 * Time Complexity: O(n log n) per test case due to sorting, and O(n) for the main loop.
 * Space Complexity: O(n) for storing the array and auxiliary data structure.
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>

#define getchar()                                                              \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2)     \
       ? EOF                                                                   \
       : *p1++)
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
char buf[1 << 23], *p1 = buf, *p2 = buf;
ll n, a[N], c;
struct aa {
  ll x, y;
  bool operator<(const aa &b) const { return x > b.x; }
} pt[N];
ll read() {
  ll res = 0, fl = 0;
  char a = getchar();
  while (a < '0' || a > '9')
    fl |= a == '-', a = getchar();
  while (a >= '0' && a <= '9')
    res = res * 10 + a - '0', a = getchar();
  return fl ? -res : res;
}
int main() {
  int i, j, t = read();
  while (t--) {
    n = read(), c = read();
    for (i = 1; i <= n; i++)
      a[i] = read(), i > 1 && (pt[i - 1] = aa{a[i] - i * c, a[i]}, 0);
    // Sorting is based on the computed value (a[i] - i * c) in descending order
    sort(pt + 1, pt + n);
    for (i = 1; i < n; i++) {
      // If the accumulated sum from node 1 is insufficient to connect with current node, break
      if (pt[i].x + a[1] < 0)
        break;
      else
        // Add the population of the current node to node 1's component
        a[1] += pt[i].y;
    }
    // If we could connect all nodes to node 1, the graph is connected
    if (i == n)
      cout << "Yes\n";
    else
      cout << "No\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/