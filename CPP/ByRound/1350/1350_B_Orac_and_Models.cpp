// Problem: CF 1350 B - Orac and Models
// https://codeforces.com/contest/1350/problem/B

/*
B. Orac and Models
Algorithms/Techniques: Dynamic Programming with Divisibility Check

Time Complexity: O(n * log(n)) per test case
Space Complexity: O(n)

The problem asks to find the maximum number of models that can be selected such that:
1. Their indices form a sequence where each index is divisible by the previous one.
2. Their sizes are strictly increasing.

This is solved using dynamic programming:
- For each position p, we compute the longest increasing subsequence ending at p,
  where indices follow divisibility rule.
- We iterate over all multiples of p and update the DP value accordingly.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> s(n + 1); // Store sizes with 1-based indexing
    for (long p = 1; p <= n; p++) {
      scanf("%ld", &s[p]);
    }
    std::vector<long> a(n + 1, 1); // DP array: max length ending at index i
    long mx(1); // Maximum length found so far
    for (long p = 1; p <= n; p++) {
      for (long q = 2 * p; q <= n; q += p) { // Iterate over multiples of p
        if (s[p] < s[q]) { // Check size condition
          a[q] = (a[q] > (a[p] + 1)) ? a[q] : (a[p] + 1); // Update DP value
          mx = (mx > a[q]) ? mx : a[q]; // Update maximum
        }
      }
    }
    printf("%ld\n", mx);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/