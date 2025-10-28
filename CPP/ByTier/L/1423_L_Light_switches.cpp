// Problem: CF 1423 L - Light switches
// https://codeforces.com/contest/1423/problem/L

/*
Problem: L. Light switches
Purpose: Given N light bulbs and S switches that toggle subsets of bulbs, determine minimum number of switches to turn all bulbs off for each day's configuration.
Algorithm: Meet-in-the-middle with bit manipulation for subset enumeration.
Time Complexity: O(S * 2^(S/2) + D * 2^(S/2))
Space Complexity: O(2^(S/2))

Input Format:
- N, S, D
- S lines describing each switch (C_i followed by C_i indices)
- D lines describing each day's bulb states (T_i followed by T_i indices)

Output Format:
- For each day, minimum switches needed or -1 if impossible.
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <random>
#include <unordered_map>

using namespace std;
#define MX 1050
typedef unsigned long long ull;
ull hs[MX], hL[1 << 15], bs[50]; // hs: random hashes, hL: left half results, bs: switch effects

int main() {
  mt19937_64 rnd(time(0)); // Random number generator
  srand(time(0));
  int n, s, d;
  scanf("%d%d%d", &n, &s, &d);
  
  // Generate random hashes for each bulb (used for hashing states)
  for (int i = 0; i < MX; i++)
    hs[i] = rnd();
  random_shuffle(hs, hs + MX); // Shuffle to ensure uniqueness
  
  // Read switch effects and compute their XOR hash representations
  for (int i = 0; i < s; i++) {
    int c;
    scanf("%d", &c);
    while (c--) {
      int k;
      scanf("%d", &k);
      bs[i] ^= hs[k]; // XOR the effect of this bulb onto the switch
    }
  }

  int mid = min(10, s / 2); // Split switches into two halves for meet-in-the-middle

  // Precompute all possible combinations for first half (2^mid)
  for (int bits = 0; bits < (1 << mid); bits++) {
    for (int i = 0; i < mid; i++) {
      if (bits >> i & 1) { // If bit i is set, include switch i
        hL[bits] ^= bs[i]; // XOR the effect of switch i
      }
    }
  }

  // Map to store hash -> minimum switches needed for right half
  unordered_map<ull, int> mp;
  mp[0] = 0; // Empty set needs 0 switches

  // Precompute all combinations for second half (2^(s-mid))
  for (int bits = 0; bits < (1 << (s - mid)); bits++) {
    ull val = 0;
    for (int i = 0; i < s - mid; i++) {
      if (bits >> i & 1) { // If bit i is set, include switch i + mid
        val ^= bs[i + mid]; // XOR the effect of switch i + mid
      }
    }
    int cnt = __builtin_popcount(bits); // Count number of switches used
    
    // Update map with minimum switches for this hash value
    if (!mp.count(val) || mp[val] > cnt) {
      mp[val] = cnt;
    }
  }

  // Process each day
  while (d--) {
    int c;
    scanf("%d", &c);
    ull v = 0; // Target state to achieve (current bulb states)
    while (c--) {
      int k;
      scanf("%d", &k);
      v ^= hs[k]; // XOR current bulb into target
    }

    int res = INT_MAX;
    
    // Try all combinations of left half switches
    for (int bits = 0; bits < (1 << mid); bits++) {
      ull val = hL[bits] ^ v; // Combine left part with target
      
      if (mp.count(val)) // If complement exists in map
        res = min(res, mp[val] + __builtin_popcount(bits)); // Update minimum switches needed
    }

    if (res == INT_MAX)
      puts("-1"); // Impossible to turn off all lights
    else
      printf("%d\n", res); // Output minimum switches
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/