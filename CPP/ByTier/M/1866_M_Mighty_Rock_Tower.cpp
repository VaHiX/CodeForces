// Problem: CF 1866 M - Mighty Rock Tower
// https://codeforces.com/contest/1866/problem/M

/*
M. Mighty Rock Tower
Algorithms/Techniques: Dynamic Programming with Probability, Modular Arithmetic, Fast Exponentiation

Time Complexity: O(N * log(mod)) due to modular exponentiations and loop over 100 possible heights
Space Complexity: O(N) for arrays p, f, pp, sum

The problem involves computing the expected number of moves to build a tower of height N,
where each move has a probability of failure that depends on the current height.
We use dynamic programming with probability transitions and modular arithmetic.
*/

#include <iostream>

#define int long long
using namespace std;
const int mod = 998244353, N = 200005;

// Fast modular exponentiation: computes (x^y) % mod
int qpow(int x, int y) {
  return y ? qpow(x * x % mod, y >> 1) * (y & 1 ? x : 1) % mod : 1;
}

int n, p[N], f[N], pp[N], sum[N];

signed main() {
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> p[i]; // Read the probability array P

  // Precompute pp[i] = i * (100)^(-1) mod mod
  for (int i = 0; i <= 99; i++)
    pp[i] = i * qpow(100, mod - 2) % mod;

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    // f[i] represents expected number of moves to complete building rock i
    f[i] = sum[p[i]] * pp[p[i]] % mod; // Transition based on probability
    f[i]++, (f[i] *= qpow((mod + 1 - pp[p[i]]) % mod, mod - 2)) %= mod; // Apply inverse to (1 - p[i] / 100)
    ans += f[i]; // Accumulate answer

    // Update sum for all possible heights j using current f[i]
    for (int j = 0; j < 100; j++)
      sum[j] = (sum[j] + f[i]) * pp[j] % mod;
  }
  cout << ans % mod;
  return 0;
}


// https://github.com/VaHiX/codeForces/