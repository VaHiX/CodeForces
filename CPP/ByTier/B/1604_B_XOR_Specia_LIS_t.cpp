// Problem: CF 1604 B - XOR Specia-LIS-t
// https://codeforces.com/contest/1604/problem/B

/*
B. XOR Specia-LIS-t
Algorithms/Techniques: Greedy, LIS length analysis, XOR properties
Time Complexity: O(n) amortized per test case
Space Complexity: O(1)

The problem asks whether we can split a sequence into subarrays such that 
the XOR of the lengths of longest increasing subsequences (LIS) of each subarray equals 0.

Key insight:
- For any subarray, the LIS length is at least 1.
- If we can partition the array into two parts where both have LIS ≥ 2,
  then we could get XOR = 0 by choosing appropriate splits.
- The only time it's impossible to achieve XOR = 0 is when n is odd and all elements form a strictly increasing sequence (LIS = n),
  because such a case leads to an odd number of LIS lengths, all ≥ 2, so their XOR is never 0.

This code checks for this specific edge case: if the whole array is strictly increasing,
and its length is odd, it outputs "NO", otherwise "YES".
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long prev;
    scanf("%ld", &prev);
    bool inc(true); // Tracks if the sequence is strictly increasing
    for (long p = 1; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x <= prev) {
        inc = false; // Not strictly increasing anymore
      }
      prev = x;
    }
    // If the whole sequence is strictly increasing and has odd length, we cannot split it to make XOR 0
    puts((n % 2) && inc ? "NO" : "YES");
  }
}


// https://github.com/VaHiX/codeForces/