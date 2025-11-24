// Problem: CF 639 B - Bear and Forgotten Tree 3
// https://codeforces.com/contest/639/problem/B

/*
 * Purpose: This program determines whether a tree with given number of vertices (n),
 * diameter (d), and height (h) after rooting at vertex 1 can exist. If such a tree exists,
 * it outputs the edges of one such tree. Otherwise, it prints -1.
 *
 * Algorithm:
 * 1. Check if the given values of n, d, and h are valid.
 *    - The diameter must be at least the height.
 *    - The diameter must not exceed twice the height (because in any tree with height h,
 *      the maximum possible diameter is 2*h, which occurs in a path graph).
 * 2. Build a base path of length h starting from vertex 1.
 * 3. Depending on relationship between d and h:
 *    - If d == h, add extra vertices to the path to reach n, connecting them to vertex 2.
 *    - If d > h, extend the tree by adding vertices to create the required diameter.
 * 4. Output the constructed edges.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 1001
#define pp pair<int, int>
using namespace std;

int main() {
  int i, j, k;
  int n, h, d;
  int h2, d2;
  cin >> n >> d >> h;
  // Check invalid cases: d must be between h and 2*h
  if (d > 2 * h || d < h) {
    cout << "-1\n";
    return 0;
  }
  h2 = h;
  k = 1;
  vector<pp> v; // Vector to store edges
  // Create a path of length h starting from node 1
  while (h2--) {
    v.push_back({k, k + 1});
    k++;
  }
  // If diameter equals height, we need to extend the tree
  if (d == h) {
    if (k == 2 && n > 2) {
      cout << "-1\n";
      return 0;
    }
    n -= (h + 1); // Remaining vertices
    k++;
    // Connect remaining nodes to node 2
    while (n--) {
      v.push_back({2, k});
      k++;
    }
  } else {
    // If diameter is greater than height, create a longer path
    d2 = abs(h - d); // Difference between diameter and height
    j = 1;
    k++;
    // Extend the path from node j (initially 1) to increase diameter
    while (d2--) {
      v.push_back({j, k});
      j = k;
      k++;
    }
    // Connect remaining vertices to the first node to maintain structure
    while (k <= n) {
      v.push_back({1, k});
      k++;
    }
  }
  // Print all edges
  for (pp p : v)
    cout << p.first << " " << p.second << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/