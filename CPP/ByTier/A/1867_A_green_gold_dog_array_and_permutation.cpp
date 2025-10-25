// Problem: CF 1867 A - green_gold_dog, array and permutation
// https://codeforces.com/contest/1867/problem/A

/*
 * Problem: Maximize distinct differences between array 'a' and permutation 'b'
 * Algorithm: Sort elements by value in descending order, assign ranks to original positions
 * Time Complexity: O(n log n) per test case due to sorting
 * Space Complexity: O(n) for storing the array and auxiliary vectors
 */

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<std::pair<long, long>> a(n); // Store value and original index
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p].first);  // Read value
      a[p].second = p;            // Store original index
    }
    sort(a.rbegin(), a.rend());   // Sort in descending order by value
    std::vector<long> b(n);       // Result permutation
    for (long p = 0; p < n; p++) {
      b[a[p].second] = p + 1;     // Assign rank (1-based) to original index
    }
    for (long p = 0; p < n; p++) {
      printf("%ld ", b[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/