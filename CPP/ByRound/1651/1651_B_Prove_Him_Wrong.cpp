// Problem: CF 1651 B - Prove Him Wrong
// https://codeforces.com/contest/1651/problem/B

/*
Algorithm/Technique: Number Theory, Exponential Growth
Time Complexity: O(n) per test case, where n is the length of the array.
Space Complexity: O(1) additional space (not counting the output array).

The solution leverages the fact that if we have an array of powers of 3 (1, 3, 9, 27, ...),
then for any two elements, the operation of replacing them with their absolute difference
will not reduce the total sum. This is because:
- The difference of two powers of 3 (say 3^k and 3^j where k > j) is 3^k - 3^j = 3^j(3^(k-j) - 1),
  which is always less than the sum of original elements 3^k + 3^j.
- So, when we replace 3^k and 3^j with |3^k - 3^j|, the sum does not decrease.

However, the key insight is that for n > 19, it can be proven that no such array exists.
This result is based on properties of numbers and the constraints of the operation.
*/

#include <cstdio>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    if (n > 19) {
      puts("NO");
      continue;
    }
    puts("YES");
    long x(1); // Start with 3^0 = 1
    for (long p = 0; p < n; p++) {
      printf("%ld ", x); // Print current power of 3
      x *= 3;            // Move to next power of 3
    }
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/