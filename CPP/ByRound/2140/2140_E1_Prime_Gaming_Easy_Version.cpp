// Problem: CF 2140 E1 - Prime Gaming (Easy Version)
// https://codeforces.com/contest/2140/problem/E1

/*
E1. Prime Gaming (Easy Version)
Algorithm: Game Theory + Dynamic Programming + Bitmask
Time Complexity: O(n * 2^n * k), where n <= 20, k <= n
Space Complexity: O(2^n)

This problem involves computing the sum of the final pile size over all valid configurations,
where players play optimally. It uses dynamic programming with bitmask to compute game states.
The key is tracking which positions are "good" and determining winning/losing positions using
the Sprague-Grundy theorem or similar logic.
*/

#include <algorithm>
#include <iostream>
#include <stddef.h>
#include <vector>
using namespace std;
using ll = long long;
const int MOD = 1000000007;

// Fast exponentiation with modulo
ll powmod(ll a, int e) {
  ll r = 1;
  while (e) {
    if (e & 1)
      r = r * a % MOD;
    a = a * a % MOD;
    e >>= 1;
  }
  return r;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  if (!(cin >> t))
    return 0;
  while (t--) {
    int n;
    int m;
    cin >> n >> m;
    int k;
    cin >> k;
    vector<int> c(k);
    for (int i = 0; i < k; i++)
      cin >> c[i];
    if (m == 1) {
      cout << 1 << "\n";
      continue;
    }
    vector<char> prev;
    prev.resize(2); // Base case: only one pile
    prev[0] = 1;    // Losing state
    prev[1] = 0;    // Winning state
    vector<int> gs;
    int ptr = 0;
    if (c[ptr] == 1) {
      gs.push_back(0);
      ptr++;
    }
    for (int p = 2; p <= n; p++) {
      while (ptr < k && c[ptr] <= p) {
        gs.push_back(c[ptr] - 1); // Convert to 0-based index
        ptr++;
      }
      int sz = 1 << p;
      vector<char> cur(sz, 0);
      for (int mask = 0; mask < sz; mask++) {
        char lose = 1;
        for (int b : gs) {
          if (b >= p)
            break;
          int low = mask & ((1 << b) - 1);       // Lower bits
          int high = mask >> (b + 1);            // Higher bits
          int nxt = low | (high << b);           // Reconstruct mask after removal
          if (prev[nxt]) {
            lose = 0;       // If the next state is winning, current is losing
            break;
          }
        }
        cur[mask] = lose;
      }
      prev.swap(cur);
    }
    int cnt = 0;
    int fn = 1 << n;
    for (int i = 0; i < fn; i++)
      if (prev[i])
        cnt++;
    ll tot = (powmod(2, n + 1) - (cnt % MOD) + MOD) % MOD; // Total configurations minus losing ones
    cout << tot << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/