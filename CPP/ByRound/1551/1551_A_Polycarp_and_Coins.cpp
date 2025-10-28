// Problem: CF 1551 A - Polycarp and Coins
// https://codeforces.com/contest/1551/problem/A

/*
A. Polycarp and Coins
Algorithms/Techniques: Mathematical approach to distribute coins optimally.

Time Complexity: O(1) per test case
Space Complexity: O(1)

This problem aims to find the number of 1-burle and 2-burle coins such that:
1. Their total value equals n.
2. The absolute difference between their counts is minimized.

Approach:
- Start with an initial distribution where we use as many 2-burle coins as possible (n/3 * 2), leaving a remainder.
- Distribute the remainder among 1-burle coins to minimize the difference.
- The optimal count of 1-burle coins is determined by n % 3:
    - If remainder is 0: use equal numbers of both coin types.
    - If remainder is 1: add one more 1-burle coin.
    - If remainder is 2: add one more 2-burle coin.

Test cases are handled in a loop, each processing a single value n and outputting the pair (c1, c2).
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long d = n / 3; // Base count for 2-burle coins (approximate)
    // Adjust counts based on remainder to minimize |c1 - c2|
    printf("%ld %ld\n", d + (n % 3 == 1), d + (n % 3 == 2));
  }
}


// https://github.com/VaHiX/codeForces/