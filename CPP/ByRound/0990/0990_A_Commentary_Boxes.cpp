// Problem: CF 990 A - Commentary Boxes
// https://codeforces.com/contest/990/problem/A

#include <cstdio>
typedef long long ll;
int main() {
  ll n, m, a, b;
  scanf("%lld %lld %lld %lld", &n, &m, &a, &b);
  // Calculate cost to build enough boxes to reach the next multiple of m
  ll u = (m * (1 + n / m) - n) * a;
  // Calculate cost to demolish excess boxes to reach the previous multiple of m
  ll v = (n - m * (n / m)) * b;
  // Output the minimum of the two options
  printf("%lld\n", (u < v) ? u : v);
  return 0;
}

// https://github.com/VaHiX/CodeForces/