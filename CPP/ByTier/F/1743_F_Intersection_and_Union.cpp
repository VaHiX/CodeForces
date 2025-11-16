// Problem: CF 1743 F - Intersection and Union
// https://codeforces.com/contest/1743/problem/F

/*
Purpose:
This code computes the sum of the sizes of all possible set operations (union, intersection, symmetric difference) 
on n segments, over all 3^(n-1) combinations of operations. It uses a segment tree to track which segments 
cover each point and then calculates contributions based on how many segments are involved in the operations.

Algorithms:
- Segment Tree with Lazy Propagation or point updates
- Dynamic Programming on segment tree nodes to count operations
- Modular exponentiation for powers of 2 and 3

Time Complexity: O(n * log(max_r))
Space Complexity: O(max_r)

*/
#include <algorithm>
#include <iostream>
#include <vector>

#define ll long long
#define vc vector
using namespace std;

int main() {
  ll n;
  cin >> n;
  const ll mn = 300100, mod = 998244353;
  vc<ll> tr(2 * mn, 0); // Segment tree to track maximum segment index covering a point

  // Process each segment and update the segment tree
  for (ll i = 1; i <= n; ++i) {
    ll l, r;
    cin >> l >> r;
    ++r; // Convert to half-open interval [l, r)
    // Update segment tree for range [l, r)
    for (l += mn, r += mn; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        tr[l] = max(tr[l], i), ++l; // If l is odd, it's a left child, update it
      if (r & 1)
        --r, tr[r] = max(tr[r], i); // If r is odd, it's a right child, update it
    }
  }

  // Precompute powers of 2 and 3 modulo 998244353
  vc<ll> p2(mn, 1), p3(mn, 1);
  for (ll i = 1; i < mn; ++i)
    p2[i] = (p2[i - 1] * 2LL) % mod;
  for (ll i = 1; i < mn; ++i)
    p3[i] = (p3[i - 1] * 3LL) % mod;

  ll ans = 0;
  // Iterate over all possible points in the coordinate system
  for (ll i = 0; i < mn; ++i) {
    ll las = 0;
    // Find the maximum segment index that covers point i
    for (ll j = i + mn; j >= 1; j >>= 1)
      las = max(las, tr[j]);
    
    // Based on how many segments cover this point, calculate the contribution
    if (las == 1)
      ans += p2[n - 1]; // If only one segment covers this point, there are 2^(n-1) combinations for the rest of operations
    else if (las >= 2)
      ans += p3[las - 2] * p2[n + 1 - las]; // Otherwise, there are 3^(las-2) * 2^(n+1-las) combinations
    
    ans %= mod;
  }
  cout << ans << endl;
}


// https://github.com/VaHiX/CodeForces/