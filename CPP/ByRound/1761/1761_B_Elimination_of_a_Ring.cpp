// Problem: CF 1761 B - Elimination of a Ring
// https://codeforces.com/contest/1761/problem/B

/*
 * Problem: B. Elimination of a Ring
 * Purpose: Given a cyclic sequence of integers, determine the maximum number of operations 
 *          to eliminate adjacent equal elements by erasing elements. Each operation removes 
 *          an element and if it creates adjacent equal elements, one of them is erased immediately.
 *
 * Algorithms/Techniques:
 * - Set usage to count unique elements
 * - Observations on cyclic structure and how many operations are possible based on 
 *   number of distinct values and their arrangement.
 *
 * Time Complexity: O(n log n) per test case due to set operations.
 * Space Complexity: O(n) for storing the elements in a set.
 */

#include <cstdio>
#include <set>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::set<long> s; // Set to store unique elements
    
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      s.insert(x); // Insert each element into the set
    }
    
    // If there are exactly 2 distinct elements, we can perform 1 + n/2 operations
    // Otherwise, we can perform n operations
    printf("%ld\n", (s.size() == 2) ? (1 + n / 2) : n);
  }
}


// https://github.com/VaHiX/codeForces/