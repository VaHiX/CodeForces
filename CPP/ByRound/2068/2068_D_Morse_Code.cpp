// Problem: CF 2068 D - Morse Code
// https://codeforces.com/contest/2068/problem/D

/*
D. Morse Code
Time Complexity: O(n^3)
Space Complexity: O(n^3)

This problem involves constructing an optimal prefix-free binary encoding (Morse code) for a set of characters based on their frequencies to minimize the expected transmission time.

The solution uses dynamic programming with the following approach:
1. Sort characters by frequency in descending order.
2. Use a 3D DP array where dp[i][j][k] represents the minimum cost for assigning codes to i leaves of depth 1, j leaves of depth 2, and k leaves of depth 3 in some subtree structure.
3. Reconstruct the actual encoding by backtracking through the DP table.

Algorithm:
- The problem resembles Huffman coding with a variation in how costs are calculated.
- A 3D dynamic programming approach is used where states represent numbers of nodes at different depths.
- Prefix-free constraints ensure no code is a prefix of another.
- The optimal assignment is constructed using backtracking from the DP result.
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>

int n, f[207];
int dp[207][207][207];
int v[207];     // prefix sums of sorted frequencies
int leaf[207];  // stores the number of leaves for backtracking
int p[207];     // original indices, used to map back to input order
std::vector<std::string> dep[407];  // stores encodings at each level during reconstruction
std::string ans[407];           // final answer for each character

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  std::cin >> n;
  
  // Read frequencies and scale them (multiply by 10000 as integer)
  for (int i = 1; i <= n; ++i) {
    double d;
    std::cin >> d;
    f[i] = v[i] = std::round(d * 10000);   // store rounded values
    p[i] = i;                              // track original index
  }
  
  // Sort frequencies in ascending order for prefix sum calculation
  std::sort(v + 1, v + n + 1);
  
  // Sort original indices based on descending frequency to prioritize high-frequency characters
  std::sort(p + 1, p + n + 1, [](int lhs, int rhs) { return f[lhs] > f[rhs]; });
  
  // Compute prefix sums of sorted frequencies
  for (int i = 1; i <= n; ++i) {
    v[i] += v[i - 1];
  }

  // Dynamic programming step:
  // dp[i][j][k] := minimum transmission time using i leaves at depth 1, j at depth 2, k at depth 3
  // ijk = total number of nodes to be assigned codes
  for (int ijk = n; ijk >= 1; --ijk) {        // iterate from total nodes down
    for (int j = 0; j <= ijk; ++j) {          // number of nodes at depth 2
      int min = +0x3b9aca00;                  // initialize with large value
      for (int i = 0; i + j <= ijk; ++i) {    // iterate over possible depth 1 nodes
        int k = ijk - i - j;                  // compute remaining depth 3 nodes
        
        dp[i][j][k] = +0x3b9aca00;

        if (i == 0 && j == 0) {
          if (k == n) {
            dp[i][j][k] = 0;
          }
          if (ijk + i <= n) {               // boundary handling
            min = std::min(min, dp[j + i][i][k]);
          }
          continue;
        }

        if (ijk + i <= n) {
          min = std::min(min, dp[j + i][i][k]);
        }

        dp[i][j][k] = min + v[n - k];       // add transmission cost (prefix sum)
      }
    }
  }

  // Backtracking to reconstruct encoding
  int i = 1, j = 0, k = 0, top = 0;
  
  while (i != 0 || j != 0 || k != n) {
    for (int l = 0; l <= i; ++l) {                  // find which transition is optimal
      if (i + j + k + i - l <= n &&           // check boundary condition
          dp[i][j][k] == dp[j + i - l][i - l][k + l] + v[n - k]) {
        int _i = j + i - l, _j = i - l, _k = k + l;   // update state
        i = _i, j = _j, k = _k, leaf[++top] = l;      // record number of leaves for this level
        break;
      }
    }
  }

  // Generate final encodings based on reconstructed structure
  dep[1].push_back("");     // start with empty encoding
  int c = 0;

  for (int i = 1; i <= top; ++i) {
    while (leaf[i]--) {             // process each leaf
      ans[p[++c]] = dep[i].back();  // assign current encoding to character
      dep[i].pop_back();
    }
    
    for (auto j : dep[i]) {         // generate new encodings by appending . and -
      dep[i + 1].push_back(j + ".");
      dep[i + 2].push_back(j + "-");
    }
  }

  // Output the final Morse code assignments
  for (int i = 1; i <= n; ++i) {
    std::cout << ans[i] << '\n';
  }

  return 0;
}


// https://github.com/VaHiX/codeForces/