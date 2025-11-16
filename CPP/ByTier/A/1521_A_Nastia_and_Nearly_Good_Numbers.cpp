// Problem: CF 1521 A - Nastia and Nearly Good Numbers
// https://codeforces.com/contest/1521/problem/A

/*
Code Purpose:
This code solves the problem of finding three distinct positive integers x, y, and z such that:
- Exactly one of them is "good" (divisible by A * B),
- The other two are "nearly good" (divisible by A),
- And x + y = z.

Algorithm:
1. For given A and B:
   - If B == 1, it's impossible to form a valid triple (since then A*B = A, and all numbers divisible by A would be good, not nearly good).
   - Otherwise, we construct:
       x = A            (nearly good, divisible by A)
       y = A * B        (good, divisible by A * B)
       z = A * (B + 1)  (nearly good, divisible by A)

Time Complexity: O(1) per test case
Space Complexity: O(1)
*/

#include <cstdio>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll a, b;
    scanf("%lld %lld", &a, &b);
    if (b == 1) {
      puts("NO");  // Special case where B=1 makes it impossible
      continue;
    }
    printf("YES\n%lld %lld %lld\n", a, a * b, a * (b + 1));  // Construct valid x, y, z
  }
}


// https://github.com/VaHiX/CodeForces/