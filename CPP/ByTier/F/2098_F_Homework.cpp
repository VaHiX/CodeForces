// Problem: CF 2098 F - Homework
// https://codeforces.com/contest/2098/problem/F

/*
F. Homework
Time Complexity: O(n^2 / 64) per test case, where n is the length of the strings.
Space Complexity: O(n^2 / 64) per test case due to storing basis vectors.

Algorithms/Techniques:
- Gaussian elimination over GF(2) (binary field)
- Basis reduction using row operations
- Bit manipulation for efficient vector operations

This solution determines whether two binary strings can be transformed into each other using a specific set of operations.
The key insight is that the allowed transformations correspond to linear operations in GF(2), so we can use Gaussian elimination
to determine if the two strings lie in the same linear subspace. The algorithm constructs a basis for both inputs and checks
if they have the same rank, which implies that one can be transformed to the other.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
using ull = unsigned long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  if (!(cin >> T))
    return 0;
  while (T--) {
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    int k = __builtin_ctz(n); // Count trailing zeros to find log2 of largest power of 2 dividing n
    int L = 1 << k; // L is the largest power of 2 that divides n (number of blocks)
    int m = n / L; // Size of each block
    if (L == 1) {
      cout << (s == t ? "Yes\n" : "No\n");
      continue;
    }
    if (m == 1) {
      bool any_s = false, any_t = false;
      for (char c : s)
        if (c == '1') {
          any_s = true;
          break;
        }
      for (char c : t)
        if (c == '1') {
          any_t = true;
          break;
        }
      cout << ((any_s == any_t) ? "Yes\n" : "No\n");
      continue;
    }
    int W = (m + 63) >> 6; // Number of 64-bit words needed to represent a vector of size m
    vector<pair<int, vector<ull>>> basisS; // Basis for string s
    basisS.reserve(m);
    for (int bi = 0; bi < L; bi++) {
      vector<ull> vec(W, 0ULL); // Vector representation of a block of s
      int off = bi * m;
      for (int j = 0; j < m; j++) {
        if (s[off + j] == '1') {
          int w = j >> 6, b = j & 63; // Determine word and bit position
          vec[w] |= (1ULL << b); // Set the corresponding bit
        }
      }
      // Gaussian elimination step: reduce vector with existing basis elements
      for (auto &bp : basisS) {
        int piv = bp.first;
        int w = piv >> 6, b = piv & 63; // Word and bit for pivot element
        if (vec[w] & (1ULL << b)) { // If current bit is set (pivot bit)
          auto &bv = bp.second;
          for (int ww = 0; ww < W; ww++)
            vec[ww] ^= bv[ww]; // XOR with basis vector to clear this bit
        }
      }
      int piv = -1;
      // Find the leftmost set bit in current vector to determine pivot element
      for (int w = W - 1; w >= 0; w--) {
        if (vec[w]) {
          int bit = 63 - __builtin_clzll(vec[w]); // Count leading zeros and get bit position
          piv = (w << 6) + bit;
          break;
        }
      }
      if (piv >= 0) {
        basisS.emplace_back(piv, std::move(vec)); // Add vector to basis with pivot as key
      }
    }
    int ds = (int)basisS.size(); // Dimension of the basis for s
    vector<pair<int, vector<ull>>> basisT; // Basis for string t
    basisT.reserve(m);
    for (int bi = 0; bi < L; bi++) {
      vector<ull> vec(W, 0ULL); // Vector representation of a block of t
      int off = bi * m;
      for (int j = 0; j < m; j++) {
        if (t[off + j] == '1') {
          int w = j >> 6, b = j & 63; // Determine word and bit position
          vec[w] |= (1ULL << b); // Set the corresponding bit
        }
      }
      // Gaussian elimination step: reduce vector with existing basis elements
      for (auto &bp : basisT) {
        int piv = bp.first;
        int w = piv >> 6, b = piv & 63; // Word and bit for pivot element
        if (vec[w] & (1ULL << b)) { // If current bit is set (pivot bit)
          auto &bv = bp.second;
          for (int ww = 0; ww < W; ww++)
            vec[ww] ^= bv[ww]; // XOR with basis vector to clear this bit
        }
      }
      int piv = -1;
      // Find the leftmost set bit in current vector to determine pivot element
      for (int w = W - 1; w >= 0; w--) {
        if (vec[w]) {
          int bit = 63 - __builtin_clzll(vec[w]); // Count leading zeros and get bit position
          piv = (w << 6) + bit;
          break;
        }
      }
      if (piv >= 0) {
        basisT.emplace_back(piv, std::move(vec)); // Add vector to basis with pivot as key
      }
    }
    int dt = (int)basisT.size(); // Dimension of the basis for t

    bool ok = true;
    if (ds != dt) { // If dimensions differ, strings cannot be transformed to each other
      ok = false;
    } else {
      // Check whether bases are equivalent
      for (auto &bp : basisT) {
        auto vec = bp.second; // Copy current vector from basisT
        for (auto &sp : basisS) {
          int piv = sp.first;
          int w = piv >> 6, b = piv & 63;
          if (vec[w] & (1ULL << b)) { // If this bit is set in current vector
            auto &sv = sp.second;
            for (int ww = 0; ww < W; ww++)
              vec[ww] ^= sv[ww]; // Reduce with basis vector to clear pivot bit
          }
        }
        bool nonz = false;
        for (int ww = 0; ww < W; ww++) {
          if (vec[ww]) {
            nonz = true;
            break;
          }
        }
        if (nonz) { // If the row is not all zeros, then bases are different
          ok = false;
          break;
        }
      }
    }
    cout << (ok ? "Yes\n" : "No\n");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/