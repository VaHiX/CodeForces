// Problem: CF 1900 B - Laura and Operations
// https://codeforces.com/contest/1900/problem/B

/*
B. Laura and Operations
time limit per test2 seconds
memory limit per test256 megabytes

Algorithm: 
The problem involves determining whether it's possible to reduce the board to only one type of digit (1, 2, or 3) using specific operations.
Each operation removes two different digits and writes the third digit.
This is a mathematical game where we check parity conditions based on the counts of each digit.

Time Complexity: O(1) per test case - constant time operations
Space Complexity: O(1) - only using a fixed number of variables

Key insight:
- Each operation removes 2 digits and adds 1, so total count decreases by 1
- If all counts are equal, it's possible to reduce to any digit (1 1 1)
- Otherwise, we must check whether a digit can be isolated based on parity rules:
    - For digit 1 to remain: (b + c) must be even and >= 2 * min(b, c)
    - For digit 2 to remain: (a + c) must be even and >= 2 * min(a, c)
    - For digit 3 to remain: (a + b) must be even and >= 2 * min(a, b)

However, a simpler approach is used:
- Taking mod 2 of each count to get parity
- If all parities are same => result 1 1 1 (can reduce to any)
- Else, based on which pairs have same parity, we determine which digit can remain
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c;
    scanf("%ld %ld %ld", &a, &b, &c);
    a %= 2; // Get parity of count of 1s
    b %= 2; // Get parity of count of 2s
    c %= 2; // Get parity of count of 3s
    if (a == b && b == c) { // All parities are same
      puts("1 1 1"); // Can reduce to any digit
    } else if (a == b) {
      puts("0 0 1"); // Only c can remain, others impossible
    } else if (a == c) {
      puts("0 1 0"); // Only b can remain, others impossible
    } else if (b == c) {
      puts("1 0 0"); // Only a can remain, others impossible
    } else {
      puts("0 0 0"); // No digit can remain alone (all different parities)
    }
  }
}


// https://github.com/VaHiX/codeForces/