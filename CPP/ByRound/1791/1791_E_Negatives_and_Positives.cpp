// Problem: CF 1791 E - Negatives and Positives
// https://codeforces.com/contest/1791/problem/E

/*
E. Negatives and Positives
Algorithm: Greedy approach with sign manipulation using adjacent flips.
Approach:
- For each element, if it's negative, we can flip its sign (and the next one) to make it positive.
- However, we only want to flip signs optimally to maximize the total sum.
- We keep track of the minimum absolute value in the array (`mn`) and the count of negative numbers (`negcnt`).
- If there's an odd number of negatives, one element will remain negative; otherwise, all can become positive.
- The final answer is computed by adding all elements' absolute values minus twice the smallest absolute value if there are an odd number of negatives.

Time Complexity: O(n) per test case
Space Complexity: O(1)
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long long total(0);         // Total sum of absolute values
    long mn(1e9 + 7), negcnt(0); // Minimum element, count of negatives
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x < 0) {
        negcnt = 1 - negcnt;     // Toggle sign flag for negative number
        x = -x;                  // Convert to positive for summation
      }
      total += x;                // Add absolute value to total
      mn = (mn < x ? mn : x);    // Keep track of minimum absolute value
    }
    if (negcnt) {
      total -= 2 * mn;           // Subtract twice the smallest value if negative count is odd
    }
    printf("%lld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/