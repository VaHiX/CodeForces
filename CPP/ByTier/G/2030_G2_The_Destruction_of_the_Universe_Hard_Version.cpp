// Problem: CF 2030 G2 - The Destruction of the Universe (Hard Version)
// https://codeforces.com/contest/2030/problem/G2

/*
G2. The Destruction of the Universe (Hard Version)
Algorithms/Techniques: Sweep line, combinatorics, modular arithmetic, prefix/suffix processing, Fast Fourier Transform concepts (via precomputed factorials and powers)

Time Complexity: O(N log N) per test case, where N is the number of planets.
Space Complexity: O(N) for storage of arrays and auxiliary data structures.

This problem computes the sum of scores over all non-empty subsets of intervals.
Each subset's score represents the minimum number of expansions needed to make all intervals in the subset intersect.
We use a sweep line approach:
- Process events (interval starts/end) from left to right
- Maintain counts of active intervals and their contribution to intersections
- Use combinatorics to compute contributions of valid subsets
- Modular arithmetic is used throughout.
*/

#include <algorithm>
#include <stdio.h>
#include <vector>
using namespace std;
const int MOD = 998244353;

inline void inc(int &x, int y) {
  x += y;
  if (x >= MOD)
    x -= MOD;
  else if (x < 0)
    x += MOD;
}
inline int add(int x, int y) {
  inc(x, y);
  return x;
}
inline int mul(int x, int y) { return (long long)x * y % MOD; }
int pot(int x, int y) {
  int r = 1;
  for (; y; y /= 2) {
    if (y % 2)
      r = mul(r, x);
    x = mul(x, x);
  }
  return r;
}

int solve() {
  int N;
  scanf("%d", &N);
  vector<int> pref(N + 1), suff(N + 1); // Count prefix/suffix events
  for (int i = 0; i < N; i++) {
    int l, r;
    scanf("%d%d", &l, &r);
    pref[r]++;      // Mark end of interval at r
    suff[l]++;      // Mark start of interval at l
  }

  vector<int> pw2(N + 1); // Precompute powers of 2 mod MOD
  pw2[0] = 1;
  for (int i = 1; i <= N; i++)
    pw2[i] = mul(pw2[i - 1], 2);

  vector<int> fact(N + 1), ifact(N + 1); // Precompute factorials and inverse factorials
  fact[0] = 1;
  for (int i = 1; i <= N; i++)
    fact[i] = mul(fact[i - 1], i);
  ifact[N] = pot(fact[N], MOD - 2); // Modular inverse of factorial
  for (int i = N - 1; i >= 0; i--)
    ifact[i] = mul(ifact[i + 1], i + 1);

  int sol = 0, lft = 0, rig = N;              // Counters for left/right active intervals
  int curr = 0, small = pw2[N] - 1, big = 0;  // Current score, and two combinatorial values

  auto up = [&](int &x, int y) { inc(x, add(x, y)); };   // Increment x by (x + y) mod MOD
  auto down = [&](int &x, int y) {
    inc(x, y);
    if (x % 2)
      x += MOD;
    x /= 2;
  };

  auto choose = [&](int n, int k) { // Binomial coefficient C(n,k) mod MOD
    return k < 0 || k > n ? 0 : mul(fact[n], mul(ifact[k], ifact[n - k]));
  };

  for (int i = 1; i < N; i++) {
    // Process suffix events: intervals ending at position i
    for (; suff[i]--; rig--) {
      down(small, -choose(lft + rig - 1, lft));   // Update small: number of ways to choose from remaining elements
      down(big, choose(lft + rig - 1, rig));      // Update big: inverse combinations
      down(curr, -big);                           // Subtract big from current score
    }

    // Process prefix events: intervals starting at position i
    for (; pref[i]--; lft++) {
      up(curr, small);                            // Add to score the possible intersection combinations
      up(small, -choose(lft + rig, rig - 1));     // Update small by removing choices
      up(big, choose(lft + rig, lft));            // Update big: add more valid selections
    }

    inc(sol, mul(curr, pw2[N - lft - rig])); // Accumulate final contribution with remaining power of 2
  }

  return sol;
}

int main() {
  int tc;
  scanf("%d", &tc);
  while (tc--)
    printf("%d\n", solve());
  return 0;
}


// https://github.com/VaHiX/codeForces/