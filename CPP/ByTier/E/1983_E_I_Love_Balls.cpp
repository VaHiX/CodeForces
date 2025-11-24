// Problem: CF 1983 E - I Love Balls
// https://codeforces.com/contest/1983/problem/E

/*
 * Problem: E. I Love Balls
 * 
 * Purpose: Calculate the expected scores of Alice and Bob in a turn-based ball game.
 * 
 * Algorithms/Techniques:
 * - Mathematical expectation calculation using linearity of expectation.
 * - Modular arithmetic with modular inverse.
 * 
 * Time Complexity: O(n) per test case, where n is the number of balls.
 * Space Complexity: O(1), only using a constant amount of extra space.
 * 
 * Approach:
 * - Separate special and non-special balls.
 * - For each player, compute expected score based on:
 *   - Contribution from non-special balls (sum of values)
 *   - Contribution from special balls (sum of values)
 * - Use modular inverse for division operations.
 * - Apply linearity of expectation to compute final result.
 */

#include <stdint.h>
#include <iostream>

#define _                                                                      \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);                                                                  \
  cout.tie(0);
#define show(v) cout << #v ": " << (v) << endl;
#define ll int64_t
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define MOD 1000000007
using namespace std;

// Function to compute modular inverse using extended Euclidean algorithm
ll inv(ll a, ll b) { return a > 1 ? b - inv(b % a, a) * b / a : 1; }

void solve() {
  ll n, k;
  cin >> n >> k;
  ll sa = 0, sb = 0;
  
  // Sum of values of special balls
  for (ll i = 0; i < k; i++) {
    ll t;
    cin >> t;
    sa += t;
    sa %= MOD;
  }
  
  // Sum of values of non-special balls
  for (ll i = k; i < n; i++) {
    ll t;
    cin >> t;
    sb += t;
    sb %= MOD;
  }
  
  // Compute expected contributions from non-special balls
  ll qa = (n - k + 1) / 2, qb = (n - k) / 2;
  ll div = inv(n - k, MOD);  // Modular inverse of (n - k)
  ll ca = sb * qa;           // Contribution from non-special balls for Alice
  ca %= MOD;
  ca *= div;
  ca %= MOD;
  ll cb = sb * qb;           // Contribution from non-special balls for Bob
  cb %= MOD;
  cb *= div;
  cb %= MOD;
  
  // Compute expected contributions from special balls
  ll ra = (n + 1 - k + 1) / 2, rb = (n + 1 - k) / 2;
  div = inv(n + 1 - k, MOD); // Modular inverse of (n - k + 1)
  ll da = sa * ra;           // Contribution from special balls for Alice
  da %= MOD;
  da *= div;
  da %= MOD;
  ll db = sa * rb;           // Contribution from special balls for Bob
  db %= MOD;
  db *= div;
  db %= MOD;
  
  // Final expected scores
  ll ta = (ca + da) % MOD, tb = (cb + db) % MOD;
  cout << ta << ' ' << tb << '\n';
}

int main() {
  _ ll ttt = 1;
  cin >> ttt;
  while (ttt--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/