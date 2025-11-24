// Problem: CF 1918 B - Minimize Inversions
// https://codeforces.com/contest/1918/problem/B

/*
Purpose: This code aims to minimize the total number of inversions in two permutations a and b by rearranging them using swaps of corresponding elements. The strategy is to sort the pairs (a[i], b[i]) based on a[i], which results in minimizing inversions in both permutations.

Algorithm:
- Read two permutations a and b.
- Create a vector of pairs (a[i], b[i]) for all i.
- Sort the vector of pairs by the first element (a[i]).
- Output the sorted first and second elements as new permutations.

Time Complexity: O(n log n) due to sorting.
Space Complexity: O(n) for storing the vector of pairs.

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
    std::vector<std::pair<long, long>> v(n);  // Vector to store pairs of (a[i], b[i])
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p].first);  // Read a[i]
    }
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p].second);  // Read b[i]
    }
    sort(v.begin(), v.end());  // Sort pairs based on a[i] (first element)
    for (long p = 0; p < n; p++) {
      printf("%ld ", v[p].first);  // Output the sorted a values
    };
    puts("");  // New line after first permutation
    for (long p = 0; p < n; p++) {
      printf("%ld ", v[p].second);  // Output the sorted b values
    };
    puts("");  // New line after second permutation
  }
}


// https://github.com/VaHiX/CodeForces/