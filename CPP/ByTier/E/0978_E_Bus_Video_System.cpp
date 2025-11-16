// Problem: CF 978 E - Bus Video System
// https://codeforces.com/contest/978/problem/E

#include <cstdio>
typedef long long ll;
int main() {
  ll n, w;
  scanf("%lld %lld", &n, &w);
  ll mn(0), mx(0), cs(0);
  for (ll p = 0; p < n; p++) {
    ll a;
    scanf("%lld", &a);
    cs += a;  // cumulative sum of changes
    mn = (mn < cs) ? mn : cs;  // track minimum cumulative sum
    mx = (mx > cs) ? mx : cs;  // track maximum cumulative sum
  }
  ll lower = -mn;  // lower bound for initial passengers
  ll upper = w - mx;  // upper bound for initial passengers
  ll ans = upper - lower + 1;  // number of valid initial passenger counts
  ans = (ans > 0) ? ans : 0;  // handle invalid cases (negative count)
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/