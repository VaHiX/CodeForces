// Problem: CF 1249 E - By Elevator or Stairs?
// https://codeforces.com/contest/1249/problem/E

#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll n, c;
  scanf("%lld %lld", &n, &c);
  std::vector<ll> a(n); // Time to go up/down stairs between floors
  for (ll p = 1; p < n; p++) {
    scanf("%lld", &a[p]);
  }
  std::vector<ll> b(n); // Time to go up/down elevator between floors
  for (ll p = 1; p < n; p++) {
    scanf("%lld", &b[p]);
  }
  std::vector<ll> f(n, 0), g(n, c); // f[i]: min time to reach floor i using stairs; g[i]: using elevator
  // Forward pass: compute minimum time to reach each floor from floor 1
  for (ll p = 1; p < n; p++) {
    f[p] = (f[p - 1] < g[p - 1] ? f[p - 1] : g[p - 1]) + a[p]; // Min time to reach floor p using stairs
    g[p] = ((c + f[p - 1]) < g[p - 1] ? (c + f[p - 1]) : g[p - 1]) + b[p]; // Min time to reach floor p using elevator
  }
  // Backward pass: refine the values by considering paths that may go up and then down
  for (ll p = n - 2; p > 0; p--) {
    ll x = (f[p + 1] < g[p + 1] ? f[p + 1] : g[p + 1]) + a[p + 1]; // Minimum time to go up from floor p+1 to p+2
    ll y = ((c + f[p + 1]) < g[p + 1] ? (c + f[p + 1]) : g[p + 1]) + b[p + 1]; // Minimum time to go down from floor p+1 to p+2 using elevator
    f[p] = (f[p] < x) ? f[p] : x; // Update minimum time for stairs at this floor
    g[p] = (g[p] < x) ? g[p] : x; // Update minimum time for elevator at this floor
  }
  // Output the result: minimum time to reach each floor from floor 1
  for (ll p = 0; p < n; p++) {
    printf("%lld ", (f[p] < g[p]) ? f[p] : g[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/codeForces/