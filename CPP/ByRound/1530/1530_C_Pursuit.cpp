// Problem: CF 1530 C - Pursuit
// https://codeforces.com/contest/1530/problem/C

/*
C. Pursuit
Algorithm: Binary search on the number of additional stages k
Time Complexity: O(n log n) per test case due to sorting and binary search
Space Complexity: O(n) for storing the arrays

The problem involves determining the minimum number of additional stages 
needed so that your total score can become greater than or equal to Ilya's,
based on a specific scoring rule. Each contestant selects the top 
k - floor(k/4) stages and sums them up for their final score.

This solution uses binary search on the number of additional stages k, 
and for each k, checks whether it's possible to make your score >= Ilya's
by optimally choosing which scores to include.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
bool check(const std::vector<long> &a, const std::vector<long> &b, long k) {
  // Calculate how many top stages we take from 'a' and 'b'
  long ra = (a.size() - 1 + k) / 4; // Number of lowest scores to exclude from 'a'
  long rb = (b.size() - 1 + k) / 4 - k; // Adjustment for 'b'
  rb = (rb > 0 ? rb : 0); // Ensure non-negative
  // Compute the difference in total scores with optimal selections
  long diff = 100 * k + (a.back() - a[ra]) - (b.back() - b[rb]);
  return diff >= 0;
}
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n + 1);
    for (long p = 1; p <= n; p++) {
      scanf("%ld", &a[p]);
    }
    std::vector<long> b(n + 1);
    for (long p = 1; p <= n; p++) {
      scanf("%ld", &b[p]);
    }
    sort(a.begin(), a.end());
    for (long p = 1; p <= n; p++) {
      a[p] += a[p - 1]; // Prefix sum
    }
    sort(b.begin(), b.end());
    for (long p = 1; p <= n; p++) {
      b[p] += b[p - 1]; // Prefix sum
    }
    long left(0), right(n + 1), res(0);
    while (left <= right) {
      long mid = (left + right) / 2;
      if (check(a, b, mid)) {
        res = mid; // Valid number of additional stages
        right = mid - 1; // Try smaller k
      } else {
        left = mid + 1; // Need more stages
      }
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/