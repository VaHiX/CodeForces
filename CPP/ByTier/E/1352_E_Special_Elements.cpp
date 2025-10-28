// Problem: CF 1352 E - Special Elements
// https://codeforces.com/contest/1352/problem/E

/*
E. Special Elements
Algorithm: Two-pointer technique on prefix sums to find if any subarray sum equals a given element.
Time Complexity: O(n^2) per test case in worst case, but optimized with sliding window and early termination.
Space Complexity: O(n) for prefix sum array.

The array a=[a_1, a_2, ..., a_n] (1 <= a_i <= n) is given. Its element a_i is called special if there exists a pair of indices l and r (1 <= l < r <= n) such that a_i = a_l + a_{l+1} + ... + a_r. In other words, an element is called special if it can be represented as the sum of two or more consecutive elements of an array.

We use prefix sums to efficiently compute subarray sums and a two-pointer approach to check if any such sum equals a target value.
*/

#include <cstdio>
#include <vector>
bool check(std::vector<long> s, long x) {
  long l(0), r(1); // Two pointers for sliding window over prefix sums
  while (r < s.size()) {
    long cur = s[r] - ((l > 0) ? s[l - 1] : 0); // Compute subarray sum from index l to r
    if (cur == x) {
      return true; // Found a valid subarray sum matching target x
    } else if ((cur > x) && (l + 1 < r)) {
      ++l; // Shrink window from left since current sum is too large
    } else {
      ++r; // Expand window to right to increase sum
    }
  }
  return false;
}
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n), s(n); // a is input array, s is prefix sum array
    long cs(0);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
      cs += a[p]; // Compute cumulative sum
      s[p] = cs;  // Store prefix sum at index p
    }
    long cnt(0);
    for (long p = 0; p < n; p++) {
      cnt += check(s, a[p]); // Check if element a[p] is special
    }
    printf("%ld\n", cnt);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/