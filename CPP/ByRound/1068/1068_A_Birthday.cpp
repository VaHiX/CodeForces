// Problem: CF 1068 A - Birthday
// https://codeforces.com/contest/1068/problem/A

#include <cstdio>
typedef long long ll;
int main() {
  ll n, m, k, l;
  scanf("%lld %lld %lld %lld", &n, &m, &k, &l);
  ll x = (k + l + m - 1) / m;  // Binary search or direct calculation for minimum coins per friend
  printf("%lld\n", (m * x <= n) ? x : -1);  // Check if total coins needed exceed available coins
  return 0;
}


// https://github.com/VaHiX/codeForces/