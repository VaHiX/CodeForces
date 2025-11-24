// Problem: CF 1040 B - Shashlik Cooking
// https://codeforces.com/contest/1040/problem/B

#include <cstdio>
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  long m = 2 * k + 1; // size of coverage area per turn (center skewer + k on each side)
  if (n <= m) {
    // If total skewers fit within one coverage area, just turn the center skewer
    printf("1\n%ld\n", (n + 1) / 2);
  } else if (n % m == 0) {
    // If n is perfectly divisible by m, use exactly n/m turns
    printf("%ld\n", n / m);
    for (long p = k + 1; p <= n; p += m) {
      // Start from center skewer of each group and print it
      printf("%ld ", p);
    }
    puts("");
  } else if (n % m > k) {
    // If remainder is greater than k, we need one more turn to cover remaining skewers
    long a = n / m; // base number of turns
    long u = n % m; // remainder after division
    printf("%ld\n", a + 1);
    for (long p = u - k; p < n; p += m) {
      // Starting from adjusted position to cover remaining skewers
      printf("%ld ", p);
    }
    puts("");
  } else if (n % m <= k) {
    // If remainder is less than or equal to k, adjust strategy for optimal coverage
    long a = -1 + (n / m); // Adjusted base turns
    long u = m + n % m; // calculate new boundary for adjustment
    long x = u / 2; // midpoint of adjusted region
    u -= u / 2; // adjust upper bound
    long y = n + 1 - u + k; // compute final skewer to turn
    printf("%ld\n", a + 2); // number of turns needed
    for (long p = x - k; p < y; p += m) {
      // iterate through skewers in the adjusted region
      printf("%ld ", p);
    }
    printf("%ld\n", y); // print the last skewer
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/