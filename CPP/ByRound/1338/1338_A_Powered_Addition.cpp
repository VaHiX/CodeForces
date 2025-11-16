// Problem: CF 1338 A - Powered Addition
// https://codeforces.com/contest/1338/problem/A

/*
 * Problem: A. Powered Addition
 * Algorithms/Techniques: Greedy, Bit Manipulation
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 *
 * The problem asks to make an array non-decreasing by adding powers of 2 to elements.
 * We process the array from left to right and track the maximum value seen so far.
 * For each element, if it's less than the current max, we compute how much we need to add
 * to make it at least equal to the max. We then calculate the number of operations needed
 * by finding the highest bit set in that difference (since we can add 2^x in each second).
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long a;
    scanf("%ld", &a);
    long mx(a), diff(0); // 'mx' is the maximum value so far, 'diff' tracks needed operations
    for (long p = 1; p < n; p++) {
      long a;
      scanf("%ld", &a);
      if (a > mx) {
        mx = a; // Update maximum if current element is greater
      } else {
        long cur = mx - a;
        diff = (diff > cur) ? diff : cur; // Track the largest gap that needs to be filled
      }
    }
    long cnt(0);
    while (diff) { // Count number of bits in 'diff', which equals required seconds
      ++cnt;
      diff /= 2;
    }
    printf("%ld\n", cnt);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/