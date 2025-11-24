// Problem: CF 527 A - Playing with Paper
// https://codeforces.com/contest/527/problem/A

/*
 * Problem: Playing with Paper
 * Algorithm: Euclidean algorithm approach to count how many squares can be cut from a rectangle
 * Time Complexity: O(log(min(a, b))) - similar to the Euclidean GCD algorithm
 * Space Complexity: O(1) - only using a few variables
 *
 * The key idea is to repeatedly divide the larger dimension by the smaller,
 * count how many times we can cut a square, and then use the remainder
 * for the next iteration, mimicking the process of the Euclidean algorithm.
 */

#include <cstdio>
int main() {
  long long a, b;
  scanf("%lld %lld\n", &a, &b);
  long long ans(0);
  while (a > 0 && b > 0) {
    if (a > b) {
      ans += a / b;  // Count how many squares of size b x b can be cut from a x b rectangle
      a %= b;        // Remaining length after cutting
    } else {
      ans += b / a;  // Count how many squares of size a x a can be cut from b x a rectangle
      b %= a;        // Remaining length after cutting
    }
  }
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/