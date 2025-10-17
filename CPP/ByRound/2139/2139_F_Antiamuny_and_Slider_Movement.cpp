// Problem: CF 2139 F - Antiamuny and Slider Movement
// https://codeforces.com/contest/2139/problem/F

/*
 * Problem: F. Antiamuny and Slider Movement
 *
 * Purpose: This code computes the sum of final positions of each slider across all possible
 *          permutations of operations, modulo 10^9 + 7. It uses combinatorics and careful
 *          simulation with pre-processing to handle all permutations efficiently.
 *
 * Algorithms/Techniques:
 * - Preprocessing operations into a sorted list of unique delta values (x - i)
 * - Using prefix/suffix frequency tracking for left/right influence of operations
 * - Applying combinatorial logic with modular arithmetic
 * - Modular exponentiation for inverse calculations
 *
 * Time Complexity: O(q log q + n * q + n * L) where L is the number of unique deltas
 * Space Complexity: O(n + q + L) for storing operations, frequencies, and delta arrays
 */

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
static const int MOD = 1000000007;
static long long mod_pow(long long a, long long e) {
  long long r = 1 % MOD;
  while (e) {
    if (e & 1)
      r = (r * a) % MOD;
    a = (a * a) % MOD;
    e >>= 1;
  }
  return r;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  if (!(cin >> t))
    return 0;
  while (t--) {
    int n, m, q;
    cin >> n >> m >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i)
      cin >> a[i];
    vector<long long> S0(n);
    for (int k = 0; k < n; ++k)
      S0[k] = a[k] - (k + 1); // initial relative positions
    vector<vector<int>> opsPosByI(n + 1); // store positions of each operation for each slider
    vector<int> allV; // unique delta values (x - i)
    allV.reserve(q);
    vector<pair<int, int>> ops; // store all operations as pairs (i, x)
    ops.reserve(q);
    for (int _ = 0; _ < q; ++_) {
      int i, x;
      cin >> i >> x;
      ops.emplace_back(i, x);
      allV.push_back(x - i); // delta value for operation
    }
    sort(allV.begin(), allV.end());
    allV.erase(unique(allV.begin(), allV.end()), allV.end()); // remove duplicates
    int L = (int)allV.size(); // number of unique deltas
    for (auto [i, x] : ops) {
      int v = x - i;
      int pos = (int)(lower_bound(allV.begin(), allV.end(), v) - allV.begin());
      opsPosByI[i].push_back(pos); // store which delta positions correspond to which slider
    }
    long long yohaku = (long long)m - n; // total available space for movement
    vector<int> kuLo(L + 1), kuHi(L + 1), kuNagasa(L + 1); // segments' bounds and lengths
    for (int js = 0; js <= L; ++js) {
      long long lo = (js == 0 ? 1LL : (long long)allV[js - 1] + 1); // left boundary of segment
      long long hi = (js == L ? yohaku + 1 : (long long)allV[js] + 1); // right boundary
      if (lo < 1)
        lo = 1;
      if (hi > yohaku + 1)
        hi = yohaku + 1;
      int len = (hi > lo) ? (int)(hi - lo) : 0;
      kuLo[js] = (int)lo;
      kuHi[js] = (int)hi;
      kuNagasa[js] = len;
    }
    vector<int> inv(q + 1, 0); // modular inverse table
    for (int i = 1; i <= q; ++i)
      inv[i] = (int)mod_pow(i, MOD - 2);
    long long fact = 1; // factorial of q
    for (int i = 2; i <= q; ++i)
      fact = fact * i % MOD;
    vector<int> hidariFreq(L, 0), migiFreq(L, 0); // frequency of operations on left/right
    for (int i = 1; i <= n; ++i)
      for (int pos : opsPosByI[i])
        migiFreq[pos]++;
    long long hidariGoukei = 0; // accumulated count from left
    vector<long long> ans(n, 0); // final answer
    for (int k = 0; k < n; ++k) {
      int idx = k + 1; // current slider index
      // Add all operations for the current slider to left count
      for (int pos : opsPosByI[idx]) {
        hidariFreq[pos]++;
        hidariGoukei++;
      }
      long long kitai = 0; // expected position contribution
      long long hidariMae = 0, migiMae = 0; // running count from both sides
      for (int js = 0; js <= L; ++js) {
        if (js >= 1) {
          int j = js - 1;
          hidariMae += hidariFreq[j];
          migiMae += migiFreq[j];
        }
        int nagasa = kuNagasa[js];
        if (nagasa == 0)
          continue;
        long long L1 = hidariGoukei - hidariMae;
        long long R0 = migiMae;
        if (L1 + R0 > 0) {
          long long add = 1LL * (nagasa % MOD) % MOD;
          add = add * (L1 % MOD) % MOD;
          add = add * inv[L1 + R0] % MOD;
          kitai += add;
          if (kitai >= MOD)
            kitai -= MOD;
        } else {
          int lo = kuLo[js], hi = kuHi[js];
          long long take = (long long)min<long long>(S0[k], hi - 1) - (lo - 1);
          if (take > 0) {
            kitai += take % MOD;
            if (kitai >= MOD)
              kitai -= MOD;
          }
        }
      }
      long long cur = ((k + 1) % MOD + kitai) % MOD;
      ans[k] = fact * cur % MOD; // total contribution across permutations
      for (int pos : opsPosByI[idx])
        migiFreq[pos]--; // remove current slider's influence
    }
    for (int i = 0; i < n; ++i)
      cout << ans[i] << (i + 1 == n ? '\n' : ' ');
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/