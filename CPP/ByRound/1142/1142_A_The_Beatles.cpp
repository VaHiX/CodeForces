/*
 * Problem URL : https://codeforces.com/contest/1142/problem/A
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
void solve(int n, int k, int l, ll &min, ll &max) {
  l = ((l % k) + k) % k;
  int h = __gcd(k, l);
  k /= h;
  l /= h;
  int m = n;
  while (__gcd(m, k) > 1)
    m /= __gcd(m, k);
  min = std::min(min, (ll)n * k / m);
  max = std::max(max, (ll)n * k);
}
int main() {
  int n, k;
  cin >> n >> k;
  int a0, b0;
  cin >> a0 >> b0;
  ll min = (ll)1 << 60, max = 0;
  for (int a : {a0, k - a0})
    for (int b : {b0, k - b0})
      solve(n, k, a - b, min, max);
  std::cout << min << ' ' << max << '\n';
}