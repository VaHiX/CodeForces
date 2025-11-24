// Problem: CF 2161 G - Bitwise And Equals
// https://codeforces.com/contest/2161/problem/G

/*
Purpose: 
This program computes the minimum number of increment operations needed on an array 
such that the bitwise AND of all elements equals a given target value X. 
It uses a precomputed frequency table and bit manipulation techniques to efficiently 
calculate the result for multiple queries.

Algorithms/Techniques:
- Prefix sum over bitmask space
- Bit manipulation and greedy approach
- Preprocessing to support fast queries

Time Complexity: O(N + Q * B^2) where B = 20 is the number of bits
Space Complexity: O(2^B) for the frequency and count arrays
*/

#include <assert.h>
#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = int64_t;
int main() {
  ios_base::sync_with_stdio(false), cin.tie(nullptr);
  int N, Q;
  cin >> N >> Q;
  vector<int> A(N);
  for (int i = 0; i < N; i++)
    cin >> A[i];
  int B = 20;
  vector<int> freq(1 << B);
  for (int x : A)
    freq[x]++;
  vector<int> counts(1 << (B + 1), 0); // counts[i] will store sum of freq for all elements <= i in bit-reversed order
  for (int i = 0; i < (1 << B); i++) {
    counts[i] += freq[i];
  }
  // Build prefix sums for each bit position
  for (int b = 0; b < B; b++) {
    for (int i = 0; i < (1 << B); i++) {
      if (i & (1 << b))
        continue;
      counts[i] += counts[i ^ (1 << b)]; // accumulate counts in bit-sorted structure
    }
  }
  int init_and = A[0];
  for (int x : A)
    init_and &= x; // Initial AND of all elements
  vector<int> best_idx(B);
  for (int q = 0; q < Q; q++) {
    int X;
    cin >> X;
    ll ans = 0;
    int zeroed = -1;
    int bad = init_and & (~X); // Mask of bits that need to be cleared
    for (int b = 0; b < B; b++) {
      if (X & (1 << b)) {
        int V = (X >> b) << b; // Get the prefix of X with bit b set to 0
        int cnt = counts[V ^ (1 << b)] - counts[V]; // Number of elements matching prefix part of V
        for (int j = 0; j <= b; j++) {
          if (X & (1 << j)) {
            ans += ll(cnt) * ll(1 << j); // Accumulate cost due to set bits
          }
        }
        if (cnt) {
          zeroed = max(zeroed, b - 1); // Track highest zeroed bit level
        }
        for (int j = 0; j < b; j++) {
          int v = counts[V ^ (1 << b) ^ (1 << j)] - counts[V ^ (1 << j)]; // Difference in counts
          ans -= ll(v) * ll(1 << j); // Adjust for overcounting
        }
      }
    }
    if (zeroed >= 0) {
      bad &= ~((1 << (zeroed + 1)) - 1); // Clear bits below zeroed level
    }
    if (bad) {
      int bad_bit = -1;
      for (int b = B - 1; b >= 0; b--) {
        if (bad & (1 << b)) {
          bad_bit = b;
          break;
        }
      }
      assert(bad_bit >= 0);
      ll diff = 1e18;
      for (int clear = bad_bit + 1; clear <= B; clear++) {
        if (X & (1 << clear))
          continue; // Skip if bit already set in target
        ll M1 = 0;
        ll M2 = 1 << clear; // Define range [M1, M2) where elements differ significantly
        if (counts[M1] - counts[M2] == 0)
          continue;
        if (counts[M1] - counts[M2] == 1)
          continue; // Already optimized case
        ll cdiff = (1 << clear); // Initial difference
        for (int j = clear - 1; j >= 0; j--) {
          if (X & (1 << j)) {
            if (counts[M1 ^ (1 << j)] - counts[M2 ^ (1 << j)] > 0) {
              M1 ^= (1 << j); // Extend prefix to increase matching
              M2 ^= (1 << j);
            } else {
              break; // Stop if no further optimization
            }
          } else {
            if (counts[M1 ^ (1 << j)] - counts[M2 ^ (1 << j)] > 0) {
              M1 ^= (1 << j);
              M2 ^= (1 << j);
              cdiff -= (1 << j); // Reduce diff by setting this bit to 0
            }
          }
        }
        diff = min(diff, cdiff); // Track minimal additional cost
      }
      assert(diff < ll(1e18));
      cout << (ans + diff) << '\n';
    } else {
      cout << ans << '\n';
    }
  }
}


// https://github.com/VaHiX/CodeForces/