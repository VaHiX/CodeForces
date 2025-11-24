// Problem: CF 1208 A - XORinacci
// https://codeforces.com/contest/1208/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, n;
    scanf("%ld %ld %ld", &a, &b, &n);
    long ans(a ^ b); // Initialize ans with XOR of a and b
    if (n % 3 == 0) {
      ans = a; // Pattern repeats every 3 steps: f(n) = a when n % 3 == 0
    } else if (n % 3 == 1) {
      ans = b; // Pattern repeats every 3 steps: f(n) = b when n % 3 == 1
    }
    printf("%ld\n", ans);
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/