// Problem: CF 2124 C - Subset Multiplication
// https://codeforces.com/contest/2124/problem/C

/*
C. Subset Multiplication
Algorithm: For each test case, we need to find a value x such that multiplying some subset of elements in a "beautiful" array a (where a[i] divides a[i+1]) by x results in the given array b.

Approach:
- The idea is to compute GCD of all elements and then process the array backwards.
- We accumulate GCD from left to right and LCM from right to left.
- The key insight involves tracking prefix GCD and suffix LCM to determine what multiplier x must be.

Time Complexity: O(n * log(max(a[i])))
Space Complexity: O(n)

*/
#include <cstdio>
#include <vector>
typedef long long ll;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a * b / gcd(a, b); }

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    ll fgcd(0), flcm(1);
    for (ll p = n - 1; p >= 0; p--) {
      fgcd = gcd(fgcd, a[p]);         // Update prefix GCD from right to left
      flcm = lcm(flcm, a[p] / fgcd);   // Compute LCM of (a[p]/fgcd) values
    }
    printf("%lld\n", flcm);
  }
}


// https://github.com/VaHiX/codeForces/