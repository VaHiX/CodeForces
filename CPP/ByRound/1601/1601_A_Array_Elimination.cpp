// Problem: CF 1601 A - Array Elimination
// https://codeforces.com/contest/1601/problem/A

/*
Algorithm: Array Elimination
Time Complexity: O(30 * n) per test case
Space Complexity: O(n)

This code determines all possible values of k for which it's possible to make all elements 
of an array equal to 0 using a specific elimination operation. The key insight is based on 
bit manipulation and the greatest common divisor (gcd) of counts of set bits at each bit position.

The algorithm works as follows:
1. For each bit position (0 to 29), count how many numbers in the array have that bit set.
2. Compute the GCD of all these counts — this gives a candidate for the final answer.
3. Output all divisors of this GCD, since k must be a divisor for valid elimination.

The logic is:
- Each elimination operation with parameter k reduces k elements by their bitwise AND.
- For k to work, the pattern of operations must allow all elements to become 0.
- The constraint leads to a mathematical relationship involving bit counts and their GCD.
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
int T, n, a[200100], m, lim;

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n), lim = 0;
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]);
    for (int i = 0; i < 30; i++) {
      m = 0;
      for (int j = 1; j <= n; j++)
        if (a[j] & (1 << i))
          m++;
      lim = __gcd(m, lim); // Compute GCD of bit counts across all bits
    }
    for (int i = 1; i <= n; i++)
      if (!(lim % i)) // Check if i divides the GCD
        printf("%d ", i);
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/