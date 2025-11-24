// Problem: CF 2095 E - Pair Count
// https://codeforces.com/contest/2095/problem/E

/*
E. Pair Count
Algorithms/Techniques: Extended Euclidean Algorithm, Modular Inverse, Hash Map
Time Complexity: O(n * log p) - due to GCD and modular inverse calculations in exgcd
Space Complexity: O(n) - for the hash map storage

You are given a prime number p, n integers a1, a2, ..., an, and an integer k.
Find the number of pairs of indexes (i,j) (1≤i<j≤n) for which (ai ⊕ aj)(a2i ⊕ a2j) ≡ k mod p.
Here ⊕ denotes the bitwise XOR operation.
*/

#include <stdio.h>
#include <map>

using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;
const int MAX = 1e4 + 10;

// Extended Euclidean algorithm to solve ax + by = gcd(a, b)
ll exgcd(ll a, ll b, ll &x, ll &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  ll g, tmp;
  g = exgcd(b, a % b, x, y);  // Recursive call to get GCD and coefficients
  tmp = x;
  x = y;
  y = tmp - a / b * y;  // Update coefficients using recurrence relation
  return g;
}

// Compute modular inverse of 'a' modulo 'p', if exists
ll inv_exgcd(ll a, ll p) {
  ll g, x, y;
  g = exgcd(a, p, x, y);  // Get GCD and coefficients
  return g == 1 ? (x % p + p) % p : -1;  // Return inverse if GCD is 1, else -1
}

int main() {
  int n, k, p, i, x, cntk, cnt0;
  ll ans, tmp;
  scanf("%d%d%d", &n, &p, &k);
  map<int, int> mp;  // Hash map to store frequency of values
  cnt0 = 0;  // Count of zeros in input
  ans = 0;   // Final answer
  for (i = 1; i <= n; i++) {
    scanf("%d", &x);
    if (x == 0)
      cnt0++;
    tmp = inv_exgcd(1LL * x * x % p * x % p, p);  // Compute modular inverse of x^3 modulo p
    if (tmp == -1)
      continue;  // Skip if no inverse exists (i.e., x is divisible by p)
    tmp = tmp * k % p;  // Multiply by k in modulo p
    if (mp.count(tmp))
      ans += mp[tmp];  // Add count of matching elements to answer
    mp[1LL * x * x % p * x % p]++;  // Store frequency of x^3 modulo p
  }
  if (k == 0)
    ans += 1LL * cnt0 * (n - cnt0);  // Special case for k = 0
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/codeForces/