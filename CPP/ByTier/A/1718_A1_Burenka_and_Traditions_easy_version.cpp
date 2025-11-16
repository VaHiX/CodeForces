// Problem: CF 1718 A1 - Burenka and Traditions (easy version)
// https://codeforces.com/contest/1718/problem/A1

/*
Purpose: 
This code solves the problem of finding the minimum time required to reduce all elements of an array to zero using XOR operations on segments.
The key insight is that XOR operations on segments can be optimized by tracking the prefix XORs and identifying when a segment can be cleared in one operation.
The algorithm uses a set to track prefix XORs and counts how many segments can be cleared in a single move.

Algorithms/Techniques:
- Prefix XOR tracking
- Set-based optimization to detect redundant operations
- Greedy approach to minimize operations

Time Complexity: O(n * log n) per test case due to set operations (insertion and lookup)
Space Complexity: O(n) for storing prefix XORs in the set

*/
#include <iostream>
#include <set>

using namespace std;
int n, x, z, sum, t;
set<int> s;
signed main() {
  cin >> t;
  while (t--) {
    z = sum = 0;
    cin >> n;
    s.clear();
    for (int i = 1; i <= n; i++) {
      cin >> x;
      z ^= x; // Compute prefix XOR
      // If prefix XOR is 0, we can clear the segment from start to current index in one operation
      // Or if we've seen this prefix XOR before, we can also clear the segment between those indices
      if (!z || s.count(z))
        s.clear(), z = 0, sum++; // Reset and increment operation count
      else
        s.insert(z); // Keep track of this prefix XOR
    }
    cout << n - sum << '\n'; // Total operations needed
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/