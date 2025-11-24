// Problem: CF 1617 B - GCD Problem
// https://codeforces.com/contest/1617/problem/B

/*
Algorithm: GCD Problem
Purpose: Given a positive integer n, find three distinct positive integers a, b, c such that a + b + c = n and gcd(a, b) = c.
Techniques: 
- Use mathematical properties of numbers and GCD.
- Handle different cases based on parity (even/odd) and modulo 4 residues.
Time Complexity: O(1) per test case
Space Complexity: O(1)

The approach leverages the fact that we can construct solutions by choosing c = 1 in most cases,
and then picking a and b such that their sum is n - c and their GCD equals c.
For c = 1, we need a and b to be coprime and sum to n - 1.
This is achievable by selecting consecutive or near-consecutive numbers depending on n's properties.

If n is even: choose a = 2, b = n - 3, c = 1. This works because gcd(2, n-3) = 1,
and 2 + (n-3) + 1 = n. Also, a, b, c are distinct when n >= 6.

If n is odd:
- If n mod 4 == 1: Try to use n/2 - 1 and n/2 + 1 as a and b. Since they are both odd and differ by 2,
  their GCD will be 1 if their difference is 2. Also 1 + (n/2 - 1) + (n/2 + 1) = n.
- If n mod 4 == 3: Similar logic but shift the numbers by 2 to ensure the GCD remains 1.
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n % 2 == 0) {
      printf("2 %ld 1\n", n - 3);
    } else if (n % 4 == 1) {
      printf("%ld %ld 1\n", n / 2 - 1, n / 2 + 1);
    } else if (n % 4 == 3) {
      printf("%ld %ld 1\n", n / 2 - 2, n / 2 + 2);
    }
  }
}


// https://github.com/VaHiX/CodeForces/