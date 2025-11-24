// Problem: CF 2137 C - Maximum Even Sum
// https://codeforces.com/contest/2137/problem/C

/*
C. Maximum Even Sum
Algorithm: Greedy + Math
Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem requires choosing an integer k such that b is divisible by k,
then multiplying a by k and dividing b by k, to maximize the even value of a+b.
The key insights are:
- For a+b to be even, both a and b must have the same parity (both odd or both even).
- If both a and b are odd, then a*b is odd, so a*b+1 makes it even.
- We can only use k if k divides b. To maximize a+b, we consider values of k that
  allow us to choose an optimal combination.

Key steps:
1. If both a and b are odd, the result is a*b + 1 (since odd*odd = odd => odd + 1 = even).
2. Else if either a or b is even or if the product is not divisible by 4, return -1.
3. Otherwise, compute a*b/2 + 2 which gives the maximum even sum.

*/

#include <stdio.h>
#include <iosfwd>

#define ll long long
using namespace std;
int t;
ll a, b;
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%lld %lld", &a, &b);
    if (a & 1 && b & 1) // both odd: product is odd, adding 1 makes even
      printf("%lld\n", a * b + 1ll);
    else if (a * b % 4 || b & 1) // if product not divisible by 4 or b is odd, impossible to form even sum with valid k
      puts("-1");
    else // otherwise compute optimal even result
      printf("%lld\n", a * b / 2 + 2);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/