// Problem: CF 2112 A - Race
// https://codeforces.com/contest/2112/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, x, y;
    scanf("%ld %ld %ld", &a, &x, &y);
    if (x > y) {
      long u = x;
      x = y;
      y = u;
    }
    // If a is within the range [x, y], then there exists a point that Alice can choose
    // such that Bob cannot guarantee to reach the prize faster regardless of where it is.
    // Otherwise, Bob can choose a point outside the range to ensure he wins.
    puts((x <= a && a <= y) ? "NO" : "YES");
  }
}

// https://github.com/VaHiX/codeForces/