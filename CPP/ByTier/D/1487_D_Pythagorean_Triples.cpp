// Problem: CF 1487 D - Pythagorean Triples
// https://codeforces.com/contest/1487/problem/D

/*
D. Pythagorean Triples
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

A Pythagorean triple is a triple of integer numbers (a, b, c) such that it is possible to form a right triangle with the lengths of the first cathetus, the second cathetus and the hypotenuse equal to a, b and c, respectively. An example of the Pythagorean triple is (3, 4, 5).

Vasya studies the properties of right triangles, and he uses a formula that determines if some triple of integers is Pythagorean. Unfortunately, he has forgotten the exact formula; he remembers only that the formula was some equation with squares. So, he came up with the following formula: c = a^2 - b.

The task is to count the number of triples (a, b, c) with 1 <= a <= b <= c <= n such that they are Pythagorean both according to the real definition and Vasya's formula.

Real Pythagorean triple: a^2 + b^2 = c^2
Vasya's formula: c = a^2 - b

Substituting Vasya's formula into the real one:
a^2 + b^2 = (a^2 - b)^2
a^2 + b^2 = a^4 - 2*a^2*b + b^2
a^2 = a^4 - 2*a^2*b
a^2*(1 - a^2) = -2*a^2*b
1 - a^2 = -2*b  (assuming a != 0)
b = (a^2 - 1)/2

This means for valid triples we must have:
- b is integer => (a^2 - 1) % 2 == 0 => a is odd
- b >= a => (a^2 - 1)/2 >= a => a^2 - 1 >= 2*a => a^2 - 2*a - 1 >= 0
- c = a^2 - b <= n => a^2 - (a^2 - 1)/2 <= n => (a^2 + 1)/2 <= n

So we iterate over odd values of 'a' and compute c = a^2 - b for each valid b.
Algorithm:
- Loop over all odd a from 3 to n
- Compute b = (a*a - 1)/2
- Compute c = a*a - b = (a*a + 1)/2
- If c <= n, increment counter

Time Complexity: O(n) worst case over all test cases due to the loop going up to n.
Space Complexity: O(1)
*/

#include <cstdio>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll cnt(0);
    for (long p = 3; p < n; p += 2) {  // iterate over odd a values starting from 3
      long tst = (p * p + 1) / 2;      // compute corresponding c value using Vasya's formula: c = (a^2 + 1)/2
      if (tst <= n) {
        ++cnt;
      } else {
        break;  // since p increases, all further values will also exceed n
      }
    }
    printf("%lld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/