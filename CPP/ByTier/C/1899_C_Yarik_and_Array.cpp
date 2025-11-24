// Problem: CF 1899 C - Yarik and Array
// https://codeforces.com/contest/1899/problem/C

/*
C. Yarik and Array

Problem Description:
Given an array of integers, find the maximum sum of a contiguous subarray such that no two adjacent elements have the same parity (i.e., alternating odd and even numbers).

Algorithm:
- This is a variant of the maximum subarray problem (Kadane's algorithm) with an added constraint.
- We use a modified version of Kadane's algorithm to track the maximum sum of valid alternating subarrays.
- As we iterate through the array, we keep track of:
  * Current sum (`cs`) of the current subarray
  * Maximum sum found so far (`mxs`)
  * Parity of the previous element (`prev`)
- Whenever we encounter an element that breaks the alternation (same parity as the previous), we reset the current sum.

Time Complexity: O(n) where n is the length of the array. Each element is processed once.
Space Complexity: O(1). Only a constant amount of extra space is used.

*/

#include <cstdio>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long prev(0), cs(0), mxs(-1007); // prev: parity of previous element, cs: current sum, mxs: max subarray sum
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      // If adding x to the current sum breaks parity alternation OR current sum is negative
      if ((prev + x) % 2 == 0 || cs < 0) {
        cs = 0; // Reset current sum
      }
      cs += x; // Add current element to the sum
      mxs = (mxs > cs ? mxs : cs); // Update maximum sum if needed
      prev = (x % 2); // Store parity of current element
    }
    printf("%ld\n", mxs);
  }
}


// https://github.com/VaHiX/codeForces/