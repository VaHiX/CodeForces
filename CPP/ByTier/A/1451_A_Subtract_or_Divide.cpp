// Problem: CF 1451 A - Subtract or Divide
// https://codeforces.com/contest/1451/problem/A

/*
Problem: Minimum Moves to Reduce N to 1
Algorithm/Techniques: Mathematical reasoning and case analysis
Time Complexity: O(1) per test case
Space Complexity: O(1)

Approach:
- If n is 1, no moves needed.
- If n is 2 or 3, we can reach 1 in 1 and 2 moves respectively.
- If n is even, we can divide by 2 to get an odd number or 1 in 1 step (if it's 2) or 2 steps (if it's greater than 2).
- If n is odd:
    - If n is a prime, we must subtract 1 (to make it even), then divide until 1 → 3 moves.
    - Otherwise, we can divide by any of its proper divisors to reduce the number in 2 steps.

This solution uses properties of numbers and divisor analysis to determine minimum steps.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n == 1) {
      puts("0"); // No moves needed
    } else if (n == 2) {
      puts("1"); // Subtract 1 to get 1
    } else if (n == 3) {
      puts("2"); // Subtract 1, then divide by 2 (2 -> 1) = 2 steps
    } else if (n % 2 == 0) {
      puts("2"); // Even numbers can be divided by 2 to get an odd number or a small even, and in worst case 2 moves needed
    } else if (n % 2) {
      puts("3"); // Odd numbers not prime, we go 3 -> 1 via divisors or subtractions = 3 steps
    } else {
      puts("-1"); // This line will never be reached due to above conditions covering all cases
    }
  }
}


// https://github.com/VaHiX/codeForces/