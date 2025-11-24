// Problem: CF 1157 A - Reachable Numbers
// https://codeforces.com/contest/1157/problem/A

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long s(n >= 10);  // Initialize s to 1 if n >= 10, else 0. This accounts for the number itself if it's >= 10.
  while (n >= 10) {
    s += (9 - n % 10);  // Add the count of reachable numbers for the current digit place
    n /= 10;            // Move to the next digit
  }
  s += 9;  // Add 9 for the base case of single digits 1-9
  printf("%ld\n", s);
  return 0;
}

// https://github.com/VaHiX/codeForces/