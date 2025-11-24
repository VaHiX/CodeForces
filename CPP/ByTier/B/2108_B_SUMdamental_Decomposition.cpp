// Problem: CF 2108 B - SUMdamental Decomposition
// https://codeforces.com/contest/2108/problem/B

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    long b(0), y(x);
    while (y) {
      b += (y % 2); // Count number of set bits in x
      y /= 2;
    }
    long ans(0);
    if (n <= b) { // If we need more elements than there are set bits in x
      ans = x;  // Just use x as the only element
    } else if ((n - b) % 2 == 0) { // If difference between n and bit count is even
      ans = x + n - b; // Add necessary number of 1s to make up for the deficit
    } else { // If difference is odd
      if (x == 0) {
        ans = (n == 1 ? -1 : (n + 3)); // Special case when x=0 and n=1, impossible; otherwise add 3
      } else if (x == 1) {
        ans = n + 3; // When x=1, we handle specially
      } else {
        ans = x + n - b + 1; // Add one extra for odd adjustment
      }
    }
    printf("%ld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/