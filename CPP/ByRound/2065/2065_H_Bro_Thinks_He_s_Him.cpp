// Problem: CF 2065 H - Bro Thinks He's Him
// https://codeforces.com/contest/2065/problem/H

/*
 * Problem: H. Bro Thinks He's Him
 * Purpose: Given a binary string and a series of flips, compute the sum of f(b) 
 *          over all non-empty subsequences b of s, where f(t) is the number of 
 *          contiguous segments of identical characters in t.
 * 
 * Algorithm:
 * - Use Binary Indexed Trees (Fenwick Trees) to maintain prefix and suffix sums efficiently.
 * - Precompute powers of 2 modulo 998244353 for fast computation.
 * - For each query, update the BITs and calculate the change in the total sum based on 
 *   the contribution of the flipped bit to all subsequences.
 * 
 * Time Complexity: O((n + q) * log n) per test case, where n is the length of the string.
 * Space Complexity: O(n) for the BITs, power array, and other auxiliary arrays.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using ll = long long;
const int MOD = 998244353;
const int MAXN = 200000 + 5;
static int fenw_pref[2][MAXN], fenw_suff[2][MAXN];
static int pow2[MAXN];

// Add value to BIT at index idx
inline void bit_add(int f[], int n, int idx, int val) {
  for (int i = idx; i <= n; i += i & -i) {
    int t = f[i] + val;
    if (t >= MOD)
      t -= MOD;
    f[i] = t;
  }
}

// Compute prefix sum up to index idx in BIT
inline int bit_sum(int f[], int idx) {
  int res = 0;
  for (int i = idx; i > 0; i -= i & -i) {
    res += f[i];
    if (res >= MOD)
      res -= MOD;
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  // Precompute powers of 2
  pow2[0] = 1;
  for (int i = 1; i < MAXN; i++) {
    pow2[i] = (int)((ll)pow2[i - 1] * 2 % MOD);
  }
  
  int t;
  cin >> t;
  while (t--) {
    string s;
    cin >> s;
    int n = (int)s.size();
    int q;
    cin >> q;
    vector<int> v(q);
    for (int i = 0; i < q; i++) {
      cin >> v[i];
    }
    
    // Initialize the BITs
    for (int c = 0; c < 2; c++) {
      for (int i = 1; i <= n; i++) {
        fenw_pref[c][i] = 0;
        fenw_suff[c][i] = 0;
      }
    }
    
    ll S1 = (ll)n * pow2[n - 1] % MOD; // Base contribution from all subsequences
    ll S2 = 0; // Dynamic contribution from individual prefix/suffix changes
    
    int sum_pow2_pref[2] = {0, 0};
    int total_suff[2] = {0, 0};
    
    // Initialize initial BITs and compute S2
    for (int j = 1; j <= n; j++) {
      int f = s[j - 1] - '0';
      S2 += (ll)sum_pow2_pref[f] * pow2[n - j] % MOD;
      if (S2 >= MOD)
        S2 -= MOD;
      sum_pow2_pref[f] += pow2[j - 1];
      if (sum_pow2_pref[f] >= MOD)
        sum_pow2_pref[f] -= MOD;
      bit_add(fenw_pref[f], n, j, pow2[j - 1]);
      bit_add(fenw_suff[f], n, j, pow2[n - j]);
      total_suff[f] = (total_suff[f] + pow2[n - j]) % MOD;
    }
    
    // Process queries
    for (int qi = 0; qi < q; qi++) {
      int pos = v[qi];
      int f_old = s[pos - 1] - '0';
      int f_new = 1 - f_old;
      
      // Calculate contributions before and after flip
      int sum_pref_old = bit_sum(fenw_pref[f_old], pos - 1);
      int sum_pref_new = bit_sum(fenw_pref[f_new], pos - 1);
      int pref_suff_old = bit_sum(fenw_suff[f_old], pos);
      int pref_suff_new = bit_sum(fenw_suff[f_new], pos);
      
      int sum_suff_old = total_suff[f_old] - pref_suff_old;
      if (sum_suff_old < 0)
        sum_suff_old += MOD;
      int sum_suff_new = total_suff[f_new] - pref_suff_new;
      if (sum_suff_new < 0)
        sum_suff_new += MOD;
      
      // Compute the change in S2
      int d1 = sum_pref_new - sum_pref_old;
      if (d1 < 0)
        d1 += MOD;
      int d2 = sum_suff_new - sum_suff_old;
      if (d2 < 0)
        d2 += MOD;
      
      ll delta = ((ll)d1 * pow2[n - pos] + (ll)d2 * pow2[pos - 1]) % MOD;
      S2 += delta;
      if (S2 >= MOD)
        S2 -= MOD;
      
      // Update BITs and total suff sums
      bit_add(fenw_pref[f_old], n, pos, (MOD - pow2[pos - 1]) % MOD);
      bit_add(fenw_suff[f_old], n, pos, (MOD - pow2[n - pos]) % MOD);
      total_suff[f_old] = (total_suff[f_old] - pow2[n - pos] + MOD) % MOD;
      bit_add(fenw_pref[f_new], n, pos, pow2[pos - 1]);
      bit_add(fenw_suff[f_new], n, pos, pow2[n - pos]);
      total_suff[f_new] = (total_suff[f_new] + pow2[n - pos]) % MOD;
      
      // Flip the character in s
      s[pos - 1] = char('0' + f_new);
      
      // Output the final answer for the current query
      int ans = (int)(S1 - S2);
      if (ans < 0)
        ans += MOD;
      cout << ans << (qi + 1 < q ? ' ' : '\n');
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/