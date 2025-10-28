// Problem: CF 1331 B - Limericks
// https://codeforces.com/contest/1331/problem/B

#include <cstdio>
int main() {
  long a;
  scanf("%ld", &a);
  long x(1), y(a);  // Initialize x=1, y=a; will store factors
  for (long p = 2; p * p <= a; p++) {  // Check divisors up to sqrt(a)
    if (a % p) {  // If p is not a divisor of a
      continue;   // Skip to next iteration
    }
    x = p;        // Found smallest prime factor
    y = a / p;    // Calculate corresponding factor
    break;        // Exit loop after finding first factor pair
  }
  printf("%ld%ld\n", x, y);  // Print the two factors concatenated
  return 0;
}


// https://github.com/VaHiX/codeForces/