// Problem: CF 1720 A - Burenka Plays with Fractions
// https://codeforces.com/contest/1720/problem/A

#include <cstdio>
typedef long long ll;
/*
Task: Burenka Plays with Fractions
Purpose: Determine the minimum number of operations (claps) to make two fractions equal.
Each operation allows multiplying either numerator or denominator of one fraction by any integer (denominator cannot be multiplied by 0).

Approach:
- Compare fractions a/b and c/d by cross-multiplying: a*d vs b*c
- If a*d == b*c, fractions are already equal -> 0 operations
- If one of the numerators is zero, we need at most 1 operation to make both zero
- Else if one cross-product is divisible by the other, we need 1 more operation
- Otherwise, we need 2 operations to adjust both fractions to a common value

Time Complexity: O(1) per test case (constant time operations)
Space Complexity: O(1) (only using fixed number of variables)

Sample Input:
8
2 1 1 1
6 3 2 1
1 2 2 3
0 1 0 100
0 1 228 179
100 3 25 6
999999999 300000000 666666666 100000000
33 15 0 84

Sample Output:
1
0
2
0
1
1
1
1
*/
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll a, b, c, d;
    scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
    ll left(b * c), right(a * d); // Cross multiply to compare fractions: a*d vs b*c
    if (left == right) {
      puts("0"); // Fractions are already equal
    } else if (left == 0 || right == 0) {
      puts("1"); // One fraction is zero, so only one operation needed to make the other also zero
    } else if (left % right == 0 || right % left == 0) {
      puts("1"); // One cross-product is divisible by the other -> one more operation suffices
    } else {
      puts("2"); // Neither fraction can be made equal in one step, so two operations needed
    }
  }
}

// https://github.com/VaHiX/codeForces/