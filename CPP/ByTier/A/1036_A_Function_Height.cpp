// Problem: CF 1036 A - Function Height
// https://codeforces.com/contest/1036/problem/A

#include <cstdio>
typedef long long ll;
int main() {
  ll n, k;
  scanf("%lld %lld", &n, &k);
  printf("%lld\n", (k + n - 1) / n); // Calculate minimum height using ceiling division
  return 0;
}


// https://github.com/VaHiX/codeForces/