// Problem: CF 2119 A - Add or XOR
// https://codeforces.com/contest/2119/problem/A

#include <cstdio>
// Problem: Make 'a' equal to 'b' using two operations: increment (cost x) or XOR with 1 (cost y)
// Time Complexity: O(1) per test case
// Space Complexity: O(1)
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, x, y;
    scanf("%ld %ld %ld %ld", &a, &b, &x, &y);
    if (a > b) {
      // If a > b, we can't increment to reach it; check if XOR operation makes a == b
      printf("%ld\n", (a ^ 1) == b ? y : -1);
    } else {
      // If a <= b, calculate the cost of converting a to b using increment and XOR operations
      long long c0 = b - a;                     // Total increments needed
      long long c1 = (b + 1) / 2 - (a + 1) / 2; // Number of odd numbers in range [a, b]
      // If y > x, it's better to use only increment operations
      // Otherwise, combine increment and XOR operations for lower cost
      printf("%lld\n", (y > x) ? (c0 * x) : ((c0 - c1) * x + c1 * y));
    }
  }
}

// https://github.com/VaHiX/codeForces/