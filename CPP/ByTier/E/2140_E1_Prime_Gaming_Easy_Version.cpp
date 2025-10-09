// Problem: CF 2140 E1 - Prime Gaming (Easy Version)
// https://codeforces.com/contest/2140/problem/E1

/*
E1. Prime Gaming (Easy Version)
Algorithm: Game Theory + Dynamic Programming + Bit Manipulation
Time Complexity: O(n * 2^n * k) per test case
Space Complexity: O(2^n) per test case

This problem involves a game played on n piles of stones, where Alice and Bob take turns removing piles.
Alice wants to maximize the final pile's value, Bob wants to minimize it. The game is modeled using 
a recursive structure with optimal play, which we simulate using dynamic programming over bitmasks.

We calculate losing positions (where current player loses) for all possible configurations using bitmask DP.
Finally, we compute sum of values in the last remaining pile across all configurations.

The key idea is to define a losing state as one where all moves lead to a winning state for the opponent.
*/

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
const int MOD = 1000000007;

// Fast exponentiation modulo MOD
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
    
    // prev stores whether a given configuration is losing (0) or winning (1)
    vector<char> prev;
    prev.resize(2);
    prev[0] = 1; // Base case: configuration (0) = losing
    prev[1] = 0; // Base case: configuration (1) = winning
    
    vector<int> gs; // List of good indices
    int ptr = 0;
    
    // If pile 1 is good, add it
    if (c[ptr] == 1) {
      gs.push_back(0); // offset by 1 for bitmask logic
      ptr++;
    }
    
    // Iterate through number of piles from 2 to n
    for (int p = 2; p <= n; p++) {
      // Add all good indices up to pile p
      while (ptr < k && c[ptr] <= p) {
        gs.push_back(c[ptr] - 1); // Adjust index for bitmask logic
        ptr++;
      }
      
      int sz = 1 << p; // Size of current bitmasks
      vector<char> cur(sz, 0); // Current DP state
      
      // For each possible configuration of p piles
      for (int mask = 0; mask < sz; mask++) {
        char lose = 1; // Assume loss initially
        
        // Try all good moves from current configuration
        for (int b : gs) {
          if (b >= p)
            break;
          
          // Compute resulting position after removing pile b+1 (0-based logic)
          int low = mask & ((1 << b) - 1);
          int high = mask >> (b + 1);
          int nxt = low | (high << b);
          
          if (prev[nxt]) {
            lose = 0;
            break;
          }
        }
        
        cur[mask] = lose;
      }
      
      prev.swap(cur); // Swap current to previous for next iteration
    }
    
    // Count losing configurations
    int cnt = 0;
    int fn = 1 << n; // Total number of configs
    
    for (int i = 0; i < fn; i++)
      if (prev[i])
        cnt++;
    
    // Result is calculated as (total possible games - losing ones)
    ll tot = (powmod(2, n + 1) - (cnt % MOD) + MOD) % MOD;
    cout << tot << "\n";
  }
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/