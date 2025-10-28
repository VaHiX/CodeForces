// Problem: CF 1366 B - Shuffle
// https://codeforces.com/contest/1366/problem/B

/*
B. Shuffle
Purpose: Determine the number of indices that can potentially hold the value 1 after a series of swap operations.
Algorithm: 
    - Use interval merging technique to find the largest continuous range that can be affected by swaps.
    - Initially, the element at position x is 1.
    - For each operation (l_i, r_i), if this interval overlaps with the current range [left, right],
      we extend the range.
    - The final result is the size of the merged interval.

Time Complexity: O(m) per test case, where m is the number of operations.
Space Complexity: O(1), only using a few variables for tracking intervals.

Input Format:
    - t: number of test cases
    - For each test case:
        - n: array size
        - x: initial position of 1
        - m: number of operations
        - m lines of l_i and r_i indicating swap ranges

Output Format:
    - For each test case, output the number of indices that can end up with value 1.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x, m;
    scanf("%ld %ld %ld", &n, &x, &m);
    long left(x), right(x); // Initialize the range containing the initial position of 1
    
    while (m--) {
      long ll, rr;
      scanf("%ld %ld", &ll, &rr);
      
      // Check if the current operation interval overlaps with [left, right]
      if (rr < left || right < ll) {
        continue; // No overlap, skip this operation
      }
      
      // Extend the range to include the current operation's interval
      left = (ll < left) ? ll : left;
      right = (rr > right) ? rr : right;
    }
    
    // Print the size of the final merged interval
    printf("%ld\n", right - left + 1);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/