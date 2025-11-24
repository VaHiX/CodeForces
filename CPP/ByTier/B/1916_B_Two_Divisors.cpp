// Problem: CF 1916 B - Two Divisors
// https://codeforces.com/contest/1916/problem/B

/*
B. Two Divisors
Algorithm: For given two largest divisors a and b of number x, we can compute x = (a * b) / gcd(a, b).
Time Complexity: O(log(min(a, b))) per test case due to GCD computation.
Space Complexity: O(1), only using constant extra space.

The problem is based on the observation that if a and b are the two largest divisors of x,
then x = (a * b) / gcd(a, b). This works because x/a and x/b are the smallest divisors greater than 1
and must be coprime with each other when a and b are the largest divisors.
*/

#include <cstdio>
long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); }
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    long g = gcd(a, b);
    // Compute x = (max(a,b) / gcd(a,b)) * b
    printf("%ld\n", ((b % a ? a : b) / g) * b);
  }
}


// https://github.com/VaHiX/codeForces/