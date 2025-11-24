// Problem: CF 1459 C - Row GCD
// https://codeforces.com/contest/1459/problem/C

/*
C. Row GCD
Algorithm: 
    - For each query b_j, we need to compute GCD(a_1 + b_j, a_2 + b_j, ..., a_n + b_j)
    - Key insight: GCD of differences between consecutive elements in sorted array helps find common divisor
    - Sort the array a, then compute GCD of all consecutive differences
    - Then for each b_j, compute GCD(a[0] + b_j, dg) where dg is the GCD of differences
    
Time Complexity: O(n log n + m * log(max(a_i))) 
Space Complexity: O(n)

*/
#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

ll gcd(ll a, ll b) { return (b == 0) ? a : gcd(b, a % b); }

int main() {
  ll n, m;
  scanf("%lld %lld", &n, &m);
  std::vector<ll> a(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &a[p]); // Read array elements
  }
  sort(a.begin(), a.end()); // Sort the array to compute differences
  
  ll dg(0); // Initialize GCD of differences
  for (ll p = 1; p < n; p++) {
    dg = gcd(dg, a[p] - a[p - 1]); // Compute GCD of consecutive differences
  }
  
  for (ll p = 0; p < m; p++) {
    ll b;
    scanf("%lld", &b); // Read query value
    b += a[0]; // Add first element to get sum
    ll res = gcd(b, dg); // Compute final GCD
    printf("%lld ", res);
  }
  puts("");
}


// https://github.com/VaHiX/codeForces/