// Problem: CF 2116 B - Gellyfish and Baby's Breath
// https://codeforces.com/contest/2116/problem/B

/*
B. Gellyfish and Baby's Breath
time limit per test1 second
memory limit per test256 megabytes

Algorithm:
- For each index i in the result array r, we compute:
  r[i] = max_{j=0}^{i} (2^{p[j]} + 2^{q[i-j]})
- Since p and q are permutations of [0, ..., n-1], we can precompute powers of 2 modulo 998244353.
- A key insight is that for a fixed i, we only need to consider the maximum values of p[j] and q[i-j]
  in the range [0, i]. This allows us to maintain running maxes over prefixes of p and q.
  
Time Complexity: O(n) per test case, due to linear iteration through arrays and prefix tracking.
Space Complexity: O(n) for storing vectors and intermediate results.

*/
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  const ll MOD = 998244353;
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> v(n, 1);  // Precompute powers of 2 modulo MOD
    for (ll p = 1; p < n; p++) {
      v[p] = (2 * v[p - 1]) % MOD;
    }
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    std::vector<ll> b(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &b[p]);
    }
    std::vector<ll> f(n);  // Result array
    ll mxa(-1), mxb(-1), wa(-1), wb(-1);  // Track max values and their indices in a and b
    for (ll p = 0; p < n; p++) {
      if (a[p] > mxa) {  // Update max of a prefix
        mxa = a[p];
        wa = p;
      }
      if (b[p] > mxb) {  // Update max of b prefix
        mxb = b[p];
        wb = p;
      }
      ll idxa(-1), idxb(-1);  // Indices to use for calculation based on current prefix comparison
      if (mxa > mxb) {
        idxa = wa;
        idxb = p - wa;
      } else if (mxa < mxb) {
        idxa = p - wb;
        idxb = wb;
      } else {
        // When maxes are equal, decide based on earlier indices
        int tsta = a[p - wb];
        int tstb = b[p - wa];
        if (tsta > tstb) {
          idxa = p - wb;
          idxb = wb;
        } else {
          idxa = wa;
          idxb = p - wa;
        }
      }
      f[p] = (v[a[idxa]] + v[b[idxb]]) % MOD;  // Compute result using precomputed powers of 2
    }
    for (ll p = 0; p < n; p++) {
      printf("%lld ", f[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/