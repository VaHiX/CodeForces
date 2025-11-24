// Problem: CF 1891 D - Suspicious logarithms
// https://codeforces.com/contest/1891/problem/D

/*
D. Suspicious logarithms
Algorithms/Techniques: Preprocessing + Range query with logarithmic decomposition

Time Complexity: O(60 * q) where 60 is the number of possible base values for f(x), 
                 and q is the number of queries.
Space Complexity: O(60) for precomputed ranges.

The solution uses a preprocessing step to compute the contribution of each interval
based on the value of f(x) = floor(log2(x)) and g(x) = floor(log_{f(x)}(x)).
It splits ranges into chunks based on powers of 2, then answers queries in O(1) time per query
by summing up contributions from precomputed intervals.
*/

#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
const ll INF = 4e18, mod = (1e9) + 7;
vector<array<ll, 3>> v;

// Adds intervals to the vector 'v' that represent how many times a particular value
// of g(x) occurs in certain ranges.
void add(ll l, ll r) {
  int b = __lg(l); // Get floor of log base 2 of l
  ll x = 1, c = 0;
  while (x < l) {
    if (x >= INF / b)
      x = INF;
    else
      x *= b;
    c++;
  }
  if (r <= x)
    v.push_back({l, r, c - 1});
  else {
    if (l < x)
      v.push_back({l, x, c - 1});
    v.push_back({x, r, c});
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  
  // Preprocessing step: generate intervals for all possible values of f(x)
  for (int m = 2; m <= 60; m++)
    add(1LL << m, 2LL << m);

  int q;
  cin >> q;
  while (q--) {
    ll l, r, res = 0;
    cin >> l >> r;
    r++;
    
    // For each precomputed interval, compute contribution to result
    for (auto [L, R, val] : v) {
      ll a = max(L, l), b = min(r, R);
      if (a < b)
        res = (res + (b - a) % mod * val) % mod;
    }
    
    cout << res << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/