// Problem: CF 1919 B - Plus-Minus Split
// https://codeforces.com/contest/1919/problem/B

/*
B. Plus-Minus Split
Algorithm/Technique: Greedy approach with prefix sum analysis
Time Complexity: O(n) per test case
Space Complexity: O(1) extra space (not counting input)

The problem asks to split a string of '+' and '-' into subarrays such that
the total penalty (defined as |sum of elements| * length of subarray) is minimized.

Key insight:
- Each character contributes +1 or -1 to the running sum.
- The optimal strategy is to avoid creating subarrays with non-zero sums,
  because those contribute penalty. 
- A subarray with sum 0 contributes 0 penalty.
- Therefore, we want to split the string such that each subarray has a sum of 0,
  if possible.
  
The approach:
- We calculate the running prefix sum (treat '+' as +1, '-' as -1).
- If the total sum is not zero, then we must have at least one subarray
  with non-zero sum.
- The minimum penalty occurs when we minimize the number of splits.
- The minimum penalty equals the absolute value of the total sum.

The code computes:
- Total sum of the array where '+' = +1, '-' = -1.
- The final penalty is simply the absolute value of this sum.
*/

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long cnt(0);
    for (long p = 0; p < n; p++) {
      // Increment by +1 if '+', decrement by -1 if '-'
      cnt += (s[p] == '+') - (s[p] == '-');
    }
    // Result is absolute value of sum
    cnt = (cnt > 0) ? cnt : -cnt;
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/