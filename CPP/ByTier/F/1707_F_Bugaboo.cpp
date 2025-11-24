// Problem: CF 1707 F - Bugaboo
// https://codeforces.com/contest/1707/problem/F

/*
 * Problem: F. Bugaboo
 * 
 * Purpose: Determine how many possible arrays 'c' are "bugaboo" (i.e., can be obtained by
 *          performing t transformations on some initial array a) after each modification.
 * 
 * Algorithms:
 * - Tree-based data structures with lazy propagation and bit manipulation.
 * - The transformation process is modeled using a binary tree with properties:
 *   - For a leaf node representing position i, value stores the fixed element or -1 (unknown).
 *   - For internal nodes, the value represents how the node contributes to the final output.
 * - The key idea is to use a sparse table or binary tree to represent the effect of t transformations.
 * 
 * Time and Space Complexity:
 * - Time: O(n * log(n) + q * log(n))
 *   - Building the tree and processing each query takes O(n * log(n)).
 *   - Each query is processed in O(log(n)) time.
 * - Space: O(n)
 *   - The memory usage is proportional to the size of the tree, which is O(n).
 * 
 * Techniques:
 * - Binary tree structure for representing XOR chains.
 * - Fast exponentiation for modular arithmetic.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int n, m, t, w;
  cin >> n >> m >> t >> w;
  // Optimize t to avoid redundant transformations
  t = min(t, 1 << __builtin_ctz(n));
  int lim = __lg(n - 1) + 1;
  // Allocate space for binary tree representation
  vector<int> a(1 << (lim + 1));
  // Initialize the leaf nodes with -1 (unknown) or 0 as needed
  for (int i = 0; i < 1 << lim; i++) {
    a[i | (1 << lim)] = i < n ? -1 : 0;
  }
  int extra = 0, bad = 0; // extra counts unknown positions, bad tracks invalid configurations
  // Update function for nodes in the tree
  auto upd = [&](int l, int i, int v) {
    // Get values of left and right child nodes
    int x = a[(2 << l) + i], y = a[(3 << l) + i], &z = a[(1 << l) + i];
    if (t >> l & 1) {
      // If the bit at position l in t is set, apply transformation
      if (!~x || !~y || x == y)
        z = x & y; // If any is unknown or equal, result is known or -1
      else
        z = 0, bad += v; // Invalid case when both known and different
    } else {
      // If the bit is not set, no transformation is applied
      if (!~x && !~y)
        z = -1, extra += v; // Both unknown, result is unknown
      else if (!~x || !~y)
        z = x | y; // One is unknown, result is known
      else
        z = x ^ y; // Both known, XOR them
    }
  };
  // Build the tree bottom-up
  for (int i = lim - 1; ~i; i--) {
    for (int j = 0; j < 1 << i; j++)
      upd(i, j, 1);
  }
  // Set function to update the leaf node and then propagate
  auto set = [&](int p, int v) {
    for (int i = lim - 1; ~i; i--) {
      upd(i, p & ((1 << i) - 1), v);
    }
  };
  // Process initial known values
  while (m--) {
    int p, v;
    cin >> p >> v, p--;
    set(p, -1); // Mark as unknown
    a[(1 << lim) + p] = v, set(p, 1); // Set value and process
  }
  int q;
  cin >> q;
  // Process queries
  while (q--) {
    int p, v, P;
    cin >> p >> v >> P, p--;
    set(p, -1);
    a[(1 << lim) + p] = v, set(p, 1);
    // If there is an invalid configuration, answer is 0
    if (bad) {
      cout << "0\n";
      continue;
    }
    // Compute (2^(w*(extra + (a[1] == -1)))) mod P using fast exponentiation
    int e = w * (extra + (a[1] == -1)), x = 1;
    for (int y = 2; e; e >>= 1, y = 1LL * y * y % P) {
      if (e & 1)
        x = 1LL * x * y % P;
    }
    cout << x << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/