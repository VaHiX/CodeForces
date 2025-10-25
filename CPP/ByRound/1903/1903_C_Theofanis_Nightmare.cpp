// Problem: CF 1903 C - Theofanis' Nightmare
// https://codeforces.com/contest/1903/problem/C

/*
C. Theofanis' Nightmare
Purpose:
  Given an array of integers, we need to partition it into non-empty subarrays such that the Cypriot value (weighted sum of subarray sums) is maximized.

Algorithm:
  Greedy approach using suffix sums.
  We iterate from right to left, maintaining a running suffix sum.
  At each step, we add the current suffix sum to the total if it's positive,
  and we also account for negative suffix sums at the end.

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the array

Techniques:
  - Suffix Sum computation
  - Greedy decision making based on sign of cumulative sum
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
    }
    long long suffix(0), total(0);
    for (long p = n - 1; p >= 0; p--) {
      suffix += v[p];           // Accumulate suffix sum from right to left
      total += suffix * (suffix > 0);  // Add suffix to total only if positive
    }
    total += suffix * (suffix < 0);  // Handle final negative suffix sum
    printf("%lld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/