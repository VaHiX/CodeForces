// Problem: CF 696 A - Lorenzo Von Matterhorn
// https://codeforces.com/contest/696/problem/A

/*
 * Problem: Barney lives in NYC with a special tree-like intersection structure where each node i is connected to 2*i and 2*i+1.
 *          There are two types of operations:
 *          1. Increase the cost of all roads on the path from u to v by w.
 *          2. Find the total cost of the path from v to u.
 *
 * Algorithm:
 * - Use a map to store the incremental costs for each road in the tree.
 * - For path updates (type 1): Traverse from both nodes towards the root until they meet,
 *   updating each edge's cost incrementally.
 * - For path queries (type 2): Similar traversal, summing up the costs of visited edges.
 *
 * Time Complexity: O(q * log(max_val)) where q is number of operations and max_val is up to 1e18.
 * Space Complexity: O(q * log(max_val)) for storing edge costs in the map.
 */

#include <stdint.h>
#include <iostream>
#include <map>
#include <utility>

int main() {
  int64_t q;
  std::cin >> q;
  // Map to store the incremental cost of each edge
  std::map<std::pair<int64_t, int64_t>, int64_t> cost;
  while (q--) {
    int64_t t, a, b;
    std::cin >> t >> a >> b;
    if (t == 1) {
      // Read the increment value
      int64_t inc;
      std::cin >> inc;
      // Traverse from a and b towards root until they meet
      while (a != b) {
        // Ensure a is smaller than b to always go up from smaller to larger
        if (a > b) {
          std::swap(a, b);
        }
        // If the edge (b/2, b) is not in cost, initialize it to 0
        if (cost.count(std::make_pair(b / 2, b)) <= 0) {
          cost[std::make_pair(b / 2, b)] = 0;
        }
        // Add the increment to the edge cost
        cost[std::make_pair(b / 2, b)] += inc;
        // Move b up to its parent
        b /= 2;
      }
    } else if (t == 2) {
      // Calculate total fee for path from a to b
      int64_t fee(0);
      while (a != b) {
        // Ensure a is smaller than b to always go up from smaller to larger
        if (a > b) {
          std::swap(a, b);
        }
        // If the edge (b/2, b) exists in cost, add its value to fee
        if (cost.count(std::make_pair(b / 2, b)) > 0) {
          fee += cost[std::make_pair(b / 2, b)];
        }
        // Move b up to its parent
        b /= 2;
      }
      // Output the total fee
      std::cout << fee << std::endl;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/