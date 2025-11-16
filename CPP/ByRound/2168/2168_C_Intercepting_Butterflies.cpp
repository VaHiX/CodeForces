// Problem: CF 2168 C - Intercepting Butterflies
// https://codeforces.com/contest/2168/problem/C

/*
Purpose: This code implements a strategy for Alice and Bob to communicate an integer x (1 <= x <= 2^15) 
         through a set S that might be altered by intercepting butterflies (adding or removing one element).
         The algorithm uses a parity-based encoding scheme to recover x in all cases.

Algorithms/Techniques:
- Bit manipulation and parity checking
- Reed-Solomon-like error correction with single error detection capability
- Encoding x into a set S of integers from 1 to 20, where the set represents bit patterns
- Decoding uses XOR operations to detect and correct single-bit errors in the set

Time Complexity: O(1) per test case (constant time since inputs are bounded)
Space Complexity: O(1) (fixed-size arrays and vectors, independent of input size)

First Run (Alice):
- Encodes x into a set S using bit manipulation and parity properties
- The set S is constructed such that even if one element is added or removed,
  the original value x can still be recovered

Second Run (Bob):
- Receives possibly modified set S'
- Reconstructs the original bit pattern using XOR operations
- Detects if an element was added or removed by checking syndrome
- Computes x from the reconstructed bits
*/

#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // Fixed positions in 1..20 that will be used for encoding (15 positions for 15 bits of x)
  const int positions[15] = {3,  5,  6,  7,  9,  10, 11, 12,
                             13, 14, 15, 17, 18, 19, 20};
  string mode;
  cin >> mode;
  if (mode == "first") { // Alice's first run
    int T;
    cin >> T;
    while (T--) {
      unsigned int x;
      cin >> x;
      unsigned int y = x - 1; // Convert to 0-based indexing
      array<unsigned char, 21> bits{}; // bits[i] represents if i is in set S (0 or 1)
      // Set bits corresponding to positions to encode x
      for (int i = 0; i < 15; ++i) {
        if ((y >> i) & 1u)
          bits[positions[i]] = 1;
      }
      // Compute parity bits for powers of 2 (1, 2, 4, 8, 16)
      for (int k = 0; k < 5; ++k) {
        int p = 1 << k; // Current power of 2
        if (p > 20)
          continue;
        unsigned char value = 0; // Compute XOR of all bits that have k-th bit set
        for (int j = 1; j <= 20; ++j) {
          if (j != p && ((j >> k) & 1)) // Skip p itself, and check if k-th bit of j is set
            value ^= bits[j];
        }
        bits[p] = value; // Store parity bit
      }
      vector<int> S;
      for (int i = 1; i <= 20; ++i)
        if (bits[i]) // Add elements to set if their bit is set
          S.push_back(i);
      cout << S.size() << "\n";
      for (int i = 0; i < (int)S.size(); ++i) {
        if (i)
          cout << " ";
        cout << S[i];
      }
      if (!S.empty())
        cout << "\n";
    }
  } else { // Bob's second run
    int T;
    cin >> T;
    while (T--) {
      int n;
      cin >> n;
      vector<int> a(n);
      for (int i = 0; i < n; ++i)
        cin >> a[i];
      array<unsigned char, 21> bits{}; // Initialize all bits to 0
      int syn = 0; // Syndrome to detect if an element was added/removed
      for (int v : a) {
        bits[v] ^= 1; // Toggle the presence of element v (since we get set S')
        syn ^= v;     // XOR all elements in set
      }
      // Check if we need to correct a single bit (element inserted/deleted)
      if (syn != 0 && syn <= 20)
        bits[syn] ^= 1; // Flip the syndrome bit if it is in valid range
      unsigned int y = 0;
      for (int i = 0; i < 15; ++i)
        if (bits[positions[i]]) // Reconstruct the original bits
          y |= (1u << i);
      cout << (y + 1u) << "\n"; // Convert back to 1-based index
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/