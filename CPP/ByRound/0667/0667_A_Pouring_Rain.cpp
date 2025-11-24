// Problem: CF 667 A - Pouring Rain
// https://codeforces.com/contest/667/problem/A

#include <cstdio>
const double PI = 3.141592653589793238462643383;
int main() {
  long d, h, v, e;
  scanf("%ld %ld %ld %ld\n", &d, &h, &v, &e);
  // Calculate the cross-sectional area of the cup: A = π * (d/2)^2 = π * d^2 /
  // 4 The rate at which water level changes is (v - e * A) / A If v <= e * A,
  // the water level will keep rising; otherwise, it can be drained
  if (4 * v <= PI * d * d * e) {
    puts("NO");
  } else {
    puts("YES");
    // Time to empty: (initial volume) / (net volume flow rate)
    // Initial volume = π * (d/2)^2 * h = π * d^2 * h / 4
    // Net rate = v - e * A = v - e * (π * d^2 / 4)
    // So time = (π * d^2 * h / 4) / (v - e * π * d^2 / 4)
    // Simplified as (π * d^2 * h) / (4 * v - π * d^2 * e)
    printf("%.7lf\n", (PI * d * d * h) / (4 * v - PI * d * d * e));
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/