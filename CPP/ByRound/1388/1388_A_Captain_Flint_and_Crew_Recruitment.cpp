// Problem: CF 1388 A - Captain Flint and Crew Recruitment
// https://codeforces.com/contest/1388/problem/A

/*
Code Purpose:
This program determines whether a given integer n can be represented as the sum of 4 different positive integers, 
where at least 3 of them are "nearly prime". A nearly prime number is defined as a product of two distinct primes p * q, 
with 1 < p < q. The solution uses a precomputed set of cases to efficiently determine the representation.

Algorithm:
- For small values of n (n <= 30), it's impossible to form such a sum, so output NO.
- Special cases for n = 36, 40, 44 are handled explicitly.
- For all other n, we use a fixed combination of three nearly primes (6, 10, 14) and compute the fourth as (n - 30).

Time Complexity: O(1) - Each test case runs in constant time.
Space Complexity: O(1) - Only a fixed amount of space is used.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n <= 30) {
      puts("NO"); // For n <= 30, it's impossible to represent n as sum of 4 distinct positive integers with at least 3 nearly primes
    } else if (n == 36 || n == 40 || n == 44) {
      // Handle special cases where n is one of these values
      printf("YES\n6 10 15 %ld\n", n - 31);  // 6=2*3, 10=2*5, 15=3*5 are nearly primes; fourth is computed
    } else {
      // General case: use 6, 10, 14 as three nearly primes
      printf("YES\n6 10 14 %ld\n", n - 30);  // Fourth number computed by subtracting 30 from n
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/