// Problem: CF 1362 A - Johnny and Ancient Computer
// https://codeforces.com/contest/1362/problem/A

/*
 * Problem: Johnny and Ancient Computer
 * Algorithm: Greedy approach with reverse operations
 * Time Complexity: O(log(max(a,b))) per test case
 * Space Complexity: O(1)
 *
 * Description:
 * We are given two numbers a and b. From a, we want to reach b using allowed operations:
 * - Multiply by 2, 4, or 8 (shift left)
 * - Divide by 2, 4, or 8 (shift right), only if divisible
 *
 * Strategy:
 * Since multiplication/division by powers of 2, we work backwards from b to a.
 * At each step, try dividing by 8, then 4, then 2 — in that order (greedy).
 * This is because larger divisions require fewer steps.
 *
 * If at any point we cannot divide (no valid division possible or division results in value < a),
 * return -1.
 *
 * Note: The algorithm is greedy and works because the optimal solution always uses the largest
 * possible division at each step, ensuring minimal steps.
 */

#include <cstdio>
typedef long long ll;

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll a, b;
    scanf("%lld %lld", &a, &b);
    if (a > b) {
      ll x = a;
      a = b;
      b = x;
    }
    int res(0);
    while (a < b) {
      // Try dividing by 8 first, then 4, then 2
      if (b % 8 == 0 && b / 8 >= a) {   // Check divisibility and whether result is still >= a
        b /= 8;
      } else if (b % 4 == 0 && b / 4 >= a) {  // Check divisibility and whether result is still >= a
        b /= 4;
      } else if (b % 2 == 0 && b / 2 >= a) {  // Check divisibility and whether result is still >= a
        b /= 2;
      } else {
        break;  // Cannot proceed further to reach 'a', so no solution
      }
      ++res;  // Increment operation count
    }
    printf("%d\n", (a == b) ? res : -1);  // Output steps if equal, otherwise -1
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/