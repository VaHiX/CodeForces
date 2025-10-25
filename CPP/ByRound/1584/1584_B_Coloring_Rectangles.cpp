// Problem: CF 1584 B - Coloring Rectangles
// https://codeforces.com/contest/1584/problem/B

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    printf("%ld\n", (m * n + 2) / 3);
  }
}


// https://github.com/VaHiX/codeForces/