// Problem: CF 1979 C - Earning on Bets
// https://codeforces.com/contest/1979/problem/C

/*
Algorithm: 
The problem requires finding a distribution of bets such that for any winning outcome,
the return (multiplier * bet) is strictly greater than the total bet amount.
This can be achieved by using the LCM of all multipliers to construct bets.
We calculate LCM of all multipliers. Then for each outcome with multiplier k_i, 
we bet s / k_i coins (where s is LCM). This ensures that for any k_i, 
the return k_i * (s / k_i) = s, which is the LCM. 
If total bet (sum of s/k_i) is less than s, we have a valid solution.
Time Complexity: O(n * log(max(k_i))) due to LCM computation for n elements
Space Complexity: O(n) for storing the multipliers and bet values
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
    std::vector<ll> v(n);
    ll s(1);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &v[p]);
      s = lcm(s, v[p]); // Compute LCM of all multipliers
    }
    ll total(0);
    for (long p = 0; p < n; p++) {
      v[p] = s / v[p]; // Bet amount for each outcome
      total += v[p];   // Calculate total bet
    }
    if (total >= s) {  // Check if total bet exceeds or equals LCM
      puts("-1");
      continue;
    }
    for (long p = 0; p < n; p++) {
      printf("%lld ", v[p]); // Output bets
    }
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/