// Problem: CF 1766 A - Extremely Round
// https://codeforces.com/contest/1766/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long res(0);
    while (n > 10) {
      res += 9;  // Add all possible extremely round numbers with same number of digits minus 1
      n /= 10;   // Move to the next digit
    }
    res += n;    // Add the first digit (which can be 1-9 for numbers like 10, 20, ..., 90)
    printf("%ld\n", res);
  }
}

// https://github.com/VaHiX/codeForces/