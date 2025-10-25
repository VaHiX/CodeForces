// Problem: CF 2070 A - FizzBuzz Remixed
// https://codeforces.com/contest/2070/problem/A

/*
Problem: FizzBuzz Remixed
Algorithm: Mathematical pattern recognition
Time Complexity: O(1) per test case
Space Complexity: O(1)

This problem asks us to count how many numbers from 0 to n (inclusive)
have the same remainder when divided by 3 and by 5.
A number i satisfies i mod 3 = i mod 5 if and only if i is of the form:
- i % 15 == 0 -> i mod 3 = 0, i mod 5 = 0
- i % 15 == 1 -> i mod 3 = 1, i mod 5 = 1
- i % 15 == 2 -> i mod 3 = 2, i mod 5 = 2

These are the valid cases for "FizzBuzz".
Since there are 3 such valid remainders (0, 1, 2) in each cycle of 15,
we can compute:
- Full cycles: (n / 15) * 3
- Remaining elements: min(3, (n % 15) + 1)
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long a = (n / 15);       // Number of complete cycles of 15
    long b = (n % 15) + 1;   // Count valid numbers in the incomplete cycle
    b = (b < 3 ? b : 3);     // At most 3 valid values per cycle
    printf("%ld\n", 3 * a + b); // Total count is full cycles * 3 + remaining
  }
}


// https://github.com/VaHiX/codeForces/