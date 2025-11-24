// Problem: CF 1926 D - Vlad and Division
// https://codeforces.com/contest/1926/problem/D

/*
D. Vlad and Division

Purpose:
This code solves the problem of dividing a list of non-negative integers into the minimum number of groups such that in any group,
no two numbers have the same bit value (0 or 1) at any of the first 31 bits.

Approach:
- For each number, we compute its "complement" value which is defined as ~x - (1 << 31).
- We use a map to track how many times a complement value has been seen.
- If a complement already exists in the map with a count > 0, we reuse that slot by decrementing the counter.
- Otherwise, we increment the group count and store the current number's complement.
- This greedy strategy ensures that numbers that have conflicting bits are separated into different groups.

Time Complexity: O(n * log n) where n is the number of elements due to map operations (log n per insertion/deletion).
Space Complexity: O(n) for storing elements in the map.

Algorithms/Techniques:
- Bit manipulation using bitwise NOT (~)
- Greedy grouping with hash map for tracking complements
- Mapping each element to its 31-bit complement to detect conflicts
*/

#include <iostream>
#include <map>
int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::map<int, int> m; // Map to count occurrences of complement values
    long cnt(0); // Counter for number of groups needed
    for (long p = 0; p < n; p++) {
      int x;
      std::cin >> x;
      // Compute the complement value and adjust by subtracting 2^31
      int y = ~x - (1 << 31);
      if (m.count(y) && m[y] > 0) {
        // If we already have a matching complement, reuse that group slot
        --m[y];
      } else {
        // Otherwise, create a new group for this number
        ++cnt;
        ++m[x]; // Store the current number's value in map (used in next iteration)
      }
    }
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/