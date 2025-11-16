// Problem: CF 792 D - Paths in a Complete Binary Tree
// https://codeforces.com/contest/792/problem/D

/*
D. Paths in a Complete Binary Tree

This problem deals with navigating a complete binary tree with n vertices, where vertices are numbered using a symmetric recursive numbering scheme.
The queries consist of starting at a given vertex and following a sequence of moves (L = left child, R = right child, U = parent).
We use bitwise operations to efficiently compute parent and child relationships without constructing the tree explicitly.

Time Complexity: O(q * m) where m is the average length of the path string in queries.
Space Complexity: O(1) - only using a constant amount of extra space.

Algorithms/Techniques:
- Bit manipulation for finding parent/child nodes
- Symmetric numbering of binary tree nodes
- Efficient traversal without constructing the tree
*/

#include <iostream>
#include <string>

typedef long long ll;
int main() {
  std::ios_base::sync_with_stdio(false);
  ll n, q;
  std::cin >> n >> q;
  while (q--) {
    ll x;                    // Current vertex number
    std::string s;           // Path string to follow
    std::cin >> x >> s;
    for (int p = 0; p < s.size(); p++) {
      if (s[p] == 'L') {     // Move to left child
        if (x & 1) {         // If x is odd, it's a leaf node, can't go left
          continue;
        }
        ll y = x & (-x);     // Get the rightmost set bit (represents distance to parent)
        x -= (y / 2);       // Move to left child: subtract half of the distance to parent
      } else if (s[p] == 'R') { // Move to right child
        if (x & 1) {         // If x is odd, it's a leaf node, can't go right
          continue;
        }
        ll y = x & (-x);     // Get the rightmost set bit
        x += (y / 2);       // Move to right child: add half of the distance to parent
      } else if (s[p] == 'U') { // Move to parent
        if (x == (n + 1) / 2) { // If x is root node, can't go up
          continue;
        }
        ll y = x & (-x);     // Get the rightmost set bit
        if (x & (2 * y)) {   // Check if x is in the right subtree of its parent
          x -= y;           // Move to parent: subtract the distance
        } else {
          x += y;           // Move to parent: add the distance
        }
      }
    }
    std::cout << x << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/