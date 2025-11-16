// Problem: CF 946 B - Weird Subtraction Process
// https://codeforces.com/contest/946/problem/B

#include <cstdio>
typedef long long ll;
int main() {
  ll a, b;
  scanf("%lld %lld", &a, &b);
  while (true) {
    // If a is at least twice b, subtract 2*b from a as many times as possible
    if (a >= 2 * b) {
      ll d = (a - b) / (2 * b);  // Calculate how many times we can subtract 2*b
      a -= d * 2 * b;            // Perform the subtraction
      if (a >= 2 * b) {          // If still greater than or equal to 2*b, subtract one more time
        a -= 2 * b;
      }
    }
    // Check if either a or b is zero, terminate if so
    if (a <= 0 || b <= 0) {
      break;
    }
    // If b is at least twice a, subtract 2*a from b as many times as possible
    if (b >= 2 * a) {
      ll d = (b - a) / (2 * a);  // Calculate how many times we can subtract 2*a
      b -= d * 2 * a;            // Perform the subtraction
      if (b >= 2 * a) {          // If still greater than or equal to 2*a, subtract one more time
        b -= 2 * a;
      }
    }
    // Check if either a or b is zero, terminate if so
    if (a <= 0 || b <= 0) {
      break;
    }
    // If neither a >= 2*b nor b >= 2*a, we are done
    if ((a < 2 * b) && (b < 2 * a)) {
      break;
    }
  }
  printf("%lld %lld\n", a, b);
  return 0;
}


// https://github.com/VaHiX/CodeForces/