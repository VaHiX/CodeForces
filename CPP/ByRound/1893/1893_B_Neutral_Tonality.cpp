// Problem: CF 1893 B - Neutral Tonality
// https://codeforces.com/contest/1893/problem/B

/*
Algorithm: Neutral Tonality
Purpose: To minimize the length of the longest increasing subsequence (LIS) after inserting all elements of array b into array a.
Approach:
- Sort array b in descending order to process larger elements first.
- Use two pointers to interleave elements from a and b in a way that minimizes LIS growth.
- The key idea is to insert elements of b such that they do not form a longer increasing subsequence.

Time Complexity: O(n log n + m log m) due to sorting b and linear scan.
Space Complexity: O(n + m) for storing arrays a, b, and final result vector f.

Techniques:
- Greedy approach
- Two-pointer technique
- Sorting
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    std::vector<long> b(m);
    for (long p = 0; p < m; p++) {
      scanf("%ld", &b[p]);
    }
    // Sort b in descending order to insert larger elements first
    sort(b.rbegin(), b.rend());
    long idxa(0), idxb(0);
    std::vector<long> f;
    // Interleave elements from a and b based on comparison
    while (f.size() < n + m && (idxa < n || idxb < m)) {
      if (idxa < n && idxb < m && a[idxa] >= b[idxb]) {
        f.push_back(a[idxa++]); // Take from a if it's >= b
      } else if (idxa < n && idxb < m && a[idxa] <= b[idxb]) {
        f.push_back(b[idxb++]); // Take from b if it's >= a
      } else if (idxa < n) {
        f.push_back(a[idxa++]); // Take remaining from a
      } else if (idxb < m) {
        f.push_back(b[idxb++]); // Take remaining from b
      } else {
        break;
      }
    }
    for (long p = 0; p < f.size(); p++) {
      printf("%ld ", f[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/