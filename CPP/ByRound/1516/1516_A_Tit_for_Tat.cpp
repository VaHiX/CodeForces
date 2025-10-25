// Problem: CF 1516 A - Tit for Tat
// https://codeforces.com/contest/1516/problem/A

/*
 * Problem: Lexicographically smallest array after at most k operations
 * Algorithm: Greedy approach - "Tit for Tat"
 * 
 * Approach:
 * To obtain the lexicographically smallest array:
 * 1. For each position from left to right, we want to minimize the value at that position.
 * 2. We can reduce current element 'a[p]' by at most min(k, a[p]) and transfer that amount to the last element.
 * 3. This ensures all elements remain non-negative and leads to lexicographically smallest result.
 *
 * Time Complexity: O(n * k) per test case
 * Space Complexity: O(n) for storing array
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    // Iterate through array from left to right
    for (long p = 0; p < n && k > 0; p++) {
      // Determine how many operations we can perform on this element
      long x = (k < a[p]) ? k : a[p];
      k -= x;
      a[p] -= x;
      a.back() += x;
    }
    for (long p = 0; p < n; p++) {
      printf("%ld ", a[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/