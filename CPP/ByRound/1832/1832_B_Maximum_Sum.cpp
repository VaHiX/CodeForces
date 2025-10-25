// Problem: CF 1832 B - Maximum Sum
// https://codeforces.com/contest/1832/problem/B

/*
B. Maximum Sum
Algorithms/Techniques: Sorting, Prefix sums, Greedy approach
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the array and prefix sum array

Problem Summary:
Given an array of distinct integers and k operations, each operation removes either:
1. Two smallest elements, or
2. One largest element.
Goal is to maximize the sum of remaining elements after exactly k operations.

Approach:
- Sort the array first.
- Use prefix sums for efficient range sum queries.
- Try all possible combinations of (i) removing two smallest elements and (ii) removing one maximum element,
  for exactly k operations, by considering how many times we perform each type of operation.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<ll> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    sort(a.begin(), a.end());
    std::vector<ll> b(n);
    b[0] = a[0];
    for (long p = 1; p < n; p++) {
      b[p] = b[p - 1] + a[p];
    }
    ll total(b[n - 1 - k]); // Initial case: remove k maximums
    for (ll p = 1; p <= k; p++) {
      // Try removing 2*p minimums and (k-p) maximums
      ll tst = b[n - 1 - k + p] - b[2 * p - 1]; // Sum of remaining elements after this operation
      total = (total > tst) ? total : tst;
    }
    printf("%lld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/