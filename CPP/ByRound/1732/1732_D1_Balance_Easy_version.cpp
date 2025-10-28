// Problem: CF 1732 D1 - Balance (Easy version)
// https://codeforces.com/contest/1732/problem/D1

#include <iostream>
#include <map>
#include <set>
#include <string>
typedef long long ll;

/**
 * Problem: D1. Balance (Easy version)
 *
 * Purpose: This code handles a dynamic set of integers and computes the k-mex for each query.
 *          The k-mex is defined as the smallest non-negative integer divisible by k that is not in the set.
 *
 * Algorithms/Techniques:
 * - Use of std::set to maintain elements in sorted order for efficient lookup
 * - Use of std::map to cache results and avoid recomputing values
 * - Optimized search using a map to track increments and skip already processed values
 *
 * Time Complexity: O(q * alpha(q)) where alpha(q) is the inverse Ackermann function, nearly constant.
 * Space Complexity: O(q), for storing the elements in set and map.
 */

int main() {
  std::ios_base::sync_with_stdio(false);
  ll q;
  std::cin >> q;
  std::set<ll> s;        // Set to store all inserted elements
  std::map<ll, ll> m;    // Map to cache incremental values for k-mex computation
  while (q--) {
    std::string u;
    ll x;
    std::cin >> u >> x;
    if (u == "+") {
      s.insert(x);       // Insert element into set
    } else if (u == "?") {
      // While there's a value in the set that is equal to m[x] + x, increment m[x]
      while (s.count(m[x] + x)) {
        m[x] += x;
      }
      std::cout << (m[x] + x) << std::endl;  // Output k-mex
    }
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/