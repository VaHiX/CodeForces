// Problem: CF 1746 A - Maxmina
// https://codeforces.com/contest/1746/problem/A

#include <cstdio>
int t, n, x, v;
int main() {
  for (scanf("%d", &t); t--; puts(x ? "YES" : "NO"))
    for (x = 0, scanf("%d%*d", &n); n--; x += v)  // Initialize x=0, read n and ignore k, loop n times
      scanf("%d", &v);  // Read next element into v, accumulate into x (sum of all elements)
}

// https://github.com/VaHiX/codeForces/