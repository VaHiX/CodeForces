// Problem: CF 1747 B - BAN BAN
// https://codeforces.com/contest/1747/problem/B

/*
Code Purpose:
This program solves the problem of modifying a string s(n) = "BAN" repeated n times,
such that the subsequence "BAN" no longer exists in the string. 
It computes the minimum number of swaps needed and outputs the sequence of swaps.

Approach:
1. The initial string s(n) is of the form "BANBANBAN...BAN" (n times).
2. To avoid the subsequence "BAN", we can strategically swap characters.
3. The optimal strategy is to swap characters at symmetric positions:
   - For indices (0, 3n-1), (3, 3n-4), etc.
   - This ensures that we don't allow a B followed by an A followed by an N to appear in order.

Time Complexity: O(n) per test case
Space Complexity: O(1) additional space (not counting input/output)

Algorithms/Techniques:
- Greedy approach using symmetric swapping to disrupt possible "BAN" subsequences
- Mathematical computation to determine number of swaps needed
*/

#include <cstdio>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    // Calculate minimum swaps needed 
    // For every 2 characters, we may need 1 swap, with an extra swap if n is odd
    printf("%ld\n", (n / 2) + (n % 2));
    // Perform swaps between symmetric indices
    for (long p = 0; p < 3 * n / 2; p += 3) {
      // Swap characters at symmetric positions to avoid BAN subsequence
      printf("%ld %ld\n", p + 1, 3 * n - p);
    }
  }
}


// https://github.com/VaHiX/CodeForces/