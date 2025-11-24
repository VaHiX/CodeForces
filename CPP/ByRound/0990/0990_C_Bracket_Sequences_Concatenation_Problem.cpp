// Problem: CF 990 C - Bracket Sequences Concatenation Problem
// https://codeforces.com/contest/990/problem/C

/*
 * Problem: Bracket Sequences Concatenation Problem
 * 
 * Algorithm/Technique:
 * - For each bracket sequence, we compute its "balance" (cur) and the minimum prefix balance (neg)
 * - A bracket sequence is valid if and only if:
 *   1. Its prefix balance never goes below 0 (neg >= 0)
 *   2. Its total balance is 0 (cur == 0)
 * - We use a map to store frequency of (cur, neg) pairs to efficiently find valid concatenations
 * - For valid concatenation s_i + s_j:
 *   - The suffix of s_i must have balance >= 0
 *   - The prefix of s_j must have balance >= 0
 *   - Total balance of s_i + s_j must be 0
 * - Time Complexity: O(N * L) where N is number of sequences and L is average length
 * - Space Complexity: O(N) for storing the map
 */

#include <iostream>
#include <map>
#include <string>
#include <utility>

typedef long long ll;

int main() {
  ll n;
  std::cin >> n;
  std::map<ll, ll> b; // Map to store frequency of valid (balance, min_prefix_balance) pairs
  
  for (ll k = 0; k < n; k++) {
    std::string s;
    std::cin >> s;
    ll cur(0), neg(0);
    for (ll p = 0; p < s.size(); p++) {
      cur += (s[p] == '(') - (s[p] == ')'); // Update current balance
      neg = (neg < cur) ? neg : cur; // Track minimum prefix balance
    }
    // Only consider sequences that can potentially form valid full brackets at the end
    if ((neg < 0) && (cur > neg)) {
      continue;
    }
    ++b[cur]; // Count sequences with same final balance
  }
  
  ll res(0);
  for (std::map<ll, ll>::iterator it = b.begin(); it != b.end(); it++) {
    ll x = it->first;
    ll cnt = it->second;
    if (x >= 0 && b.count(-x)) {
      res += cnt * b[-x]; // Count valid pairs
    }
  }
  std::cout << res << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/