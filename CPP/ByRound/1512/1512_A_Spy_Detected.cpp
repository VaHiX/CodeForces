// Problem: CF 1512 A - Spy Detected!
// https://codeforces.com/contest/1512/problem/A

/*
 * Problem: A. Spy Detected!
 * Purpose: Given an array of n positive integers where all elements are the same except one,
 *          find and output the index (1-based) of the unique element.
 *
 * Algorithms/Techniques:
 *   - Sorting the array to group identical elements together
 *   - Comparing first two elements to determine which is the outlier
 *
 * Time Complexity: O(n log n) per test case due to sorting
 * Space Complexity: O(n) for storing the vector of pairs
 */

#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<std::pair<long, long>> v(n); // Store value and original index
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p].first);  // Read the value
      v[p].second = p + 1;        // Store original 1-based index
    }
    sort(v.begin(), v.end());     // Sort by value to group identical elements
    // If first two values are equal, the outlier is at the end;
    // otherwise, the outlier is at the beginning
    long res = (v[0].first == v[1].first) ? v.back().second : v[0].second;
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/