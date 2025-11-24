// Problem: CF 1850 E - Cardboard for Pictures
// https://codeforces.com/contest/1850/problem/E

/*
E. Cardboard for Pictures

This problem involves finding the border width `w` of cardboard used to mount pictures,
given that each picture is a square with side length `s_i`, and each is mounted with
a uniform border of `w` cm on all sides.

The total cardboard area used equals:
c = sum over i of (2*w + s_i)^2

We are given the individual picture sizes and total cardboard area `c`,
and we need to determine the value of `w`.

This requires solving for an integer `w` that makes the following equation hold:
sum_{i=1}^{n} (2w + s_i)^2 = c

Reordering the equation:
sum_{i=1}^{n} (4w^2 + 4w*s_i + s_i^2) = c
4w^2 * n + 4w * sum(s_i) + sum(s_i^2) = c
4*n*w^2 + 4*sum(s_i)*w + sum(s_i^2) - c = 0

This is a quadratic in w, which can be represented as:
alpha*w^2 + beta*w + gamma = 0,
where alpha = 4*n, beta = 4*sum(s_i), gamma = sum(s_i^2) - c.

We use binary search on the value of `w` to find the smallest integer w that
satisfies the quadratic equation approximately (within floating point tolerance).

Time Complexity: O(n log(max_w)), where max_w is bounded by 1e18.
Space Complexity: O(1)

Algorithms/Techniques:
- Mathematical derivation of quadratic formula from problem constraints
- Binary search over possible values of w to find integer solution
- Floating-point arithmetic with long double for precision
*/

#include <cstdio>

typedef long double dbl;
typedef long long ll;

int main() {
  long t; // number of test cases
  scanf("%ld", &t);
  while (t--) {
    dbl n, c; // number of pictures and total cardboard used
    scanf("%Lf %Lf", &n, &c);
    dbl sum(0), ssq(0); // sum of sizes and sum of squares of sizes
    for (dbl p = 0; p < n; p++) {
      dbl x;
      scanf("%Lf", &x); // read size of one picture
      sum += x;
      ssq += x * x;
    }
    ssq -= c; // adjusting for the total cardboard used
    
    dbl alpha = 4 * n; // coefficient of w^2 in quadratic
    dbl beta = 4 * sum; // coefficient of w in quadratic
    dbl gamma = ssq; // constant term in quadratic

    dbl left(0), right(1e10 + 7); // binary search range
    long long ans(0);
    while (left <= right) {
      ll mid = (left + right) / 2;
      dbl tst = gamma + beta * mid + alpha * mid * mid; // evaluate quadratic at mid
      if (-1 < tst && tst < 1) { // close enough to zero: solution found
        ans = mid;
        break;
      } else if (tst < 0) { // too small, increase w
        left = mid + 1;
      } else if (tst > 0) { // too large, decrease w
        right = mid - 1;
      }
    }
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/