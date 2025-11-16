// Problem: CF 1611 B - Team Composition: Programmers and Mathematicians
// https://codeforces.com/contest/1611/problem/B

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    long res = (a < b ? a : b); // Take the smaller of the two counts as initial estimate
    res = (res < (a + b) / 4) ? res : (a + b) / 4; // Limit by total number of people divided by 4
    printf("%ld\n", res);
  }
}

// https://github.com/VaHiX/codeForces/