// Problem: CF 2172 L - Maximum Color Segment
// https://codeforces.com/contest/2172/problem/L

/*
 * Problem: Maximum Color Segment
 * 
 * Algorithm/Techniques: Dynamic Programming with bitmasking and sliding window concepts
 * 
 * Time Complexity: O(n * m * k) where n is length of string, m is max operations, k is window size
 * Space Complexity: O(n * m) for DP arrays
 * 
 * Approach:
 * 1. Convert string to difference array b where b[i] = 1 if s[i-1] != s[i] (representing color segment boundaries)
 * 2. For each possible window size k, we analyze segments and their contribution to maximizing color segments
 * 3. Use dynamic programming to track maximum color segments achievable with up to m operations
 * 4. For each valid window operation, calculate potential gains using bit manipulation
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, k;
  cin >> n >> m >> k;
  string s;
  cin >> s;
  if (n == 1) {
    cout << 1 << "\n";
    return 0;
  }
  int N = n - 1;
  vector<int> b(N + 1, 0);
  // b[i] = 1 if there's a color change at position i
  for (int i = 1; i <= N; i++) {
    b[i] = (s[i - 1] != s[i]) ? 1 : 0;
  }
  vector<int> bucle(N + 1, 0);
  // Mark special positions that affect the count
  if (k >= 1 && k <= N)
    bucle[k] = 1;
  int rb = n - k;
  if (rb >= 1 && rb <= N)
    bucle[rb] = 1;
  const int NEG = -1000000007;
  int M = m;
  // dp_global[i] = maximum color segments achievable with i operations
  vector<int> dp_global(M + 1, NEG);
  dp_global[0] = 0;
  int max_r = min(k, N);
  // Try each possible starting offset within the first k positions
  for (int r = 1; r <= max_r; r++) {
    vector<int> idx;
    // Collect all indices for this offset group
    for (int j = r; j <= N; j += k)
      idx.push_back(j);
    int L = (int)idx.size();
    if (L == 0)
      continue;
    vector<int> bits(L), bucles(L);
    int cnt_bucles = 0;
    // Prepare data for this group
    for (int i = 0; i < L; i++) {
      bits[i] = b[idx[i]];
      bucles[i] = bucle[idx[i]] ? 1 : 0;
      if (bucles[i])
        cnt_bucles++;
    }
    int max_ops_cad = (L - 1) + cnt_bucles;
    if (max_ops_cad > M)
      max_ops_cad = M;
    vector<int> mejor_cad(max_ops_cad + 1, NEG);
    vector<int> dp0(max_ops_cad + 1, NEG), dp1(max_ops_cad + 1, NEG);
    // Initialize base case
    if (bits[0] == 0)
      dp0[0] = 0;
    else
      dp1[0] = 0;
    
    // Process each element in group to compute optimal values
    for (int i = 0; i < L; i++) {
      if (i == L - 1) {
        // Final step - update global results
        for (int u = 0; u <= max_ops_cad; u++) {
          if (dp0[u] != NEG) {
            int base = dp0[u];
            int val = 0;
            int ylim = bucles[i] ? 1 : 0;
            for (int y = 0; y <= ylim; y++) {
              int cu = u + y;
              if (cu > max_ops_cad)
                continue;
              int fi = val ^ y;
              if (mejor_cad[cu] < base + fi)
                mejor_cad[cu] = base + fi;
            }
          }
          if (dp1[u] != NEG) {
            int base = dp1[u];
            int val = 1;
            int ylim = bucles[i] ? 1 : 0;
            for (int y = 0; y <= ylim; y++) {
              int cu = u + y;
              if (cu > max_ops_cad)
                continue;
              int fi = val ^ y;
              if (mejor_cad[cu] < base + fi)
                mejor_cad[cu] = base + fi;
            }
          }
        }
      } else {
        vector<int> ndp0(max_ops_cad + 1, NEG), ndp1(max_ops_cad + 1, NEG);
        for (int u = 0; u <= max_ops_cad; u++) {
          if (dp0[u] != NEG) {
            int base = dp0[u];
            int val = 0;
            int ylim = bucles[i] ? 1 : 0;
            for (int x = 0; x <= 1; x++) {
              for (int y = 0; y <= ylim; y++) {
                int cu = u + x + y;
                if (cu > max_ops_cad)
                  continue;
                int fi = val ^ x ^ y;
                int sig = bits[i + 1] ^ x;
                if (sig == 0) {
                  if (ndp0[cu] < base + fi)
                    ndp0[cu] = base + fi;
                } else {
                  if (ndp1[cu] < base + fi)
                    ndp1[cu] = base + fi;
                }
              }
            }
          }
          if (dp1[u] != NEG) {
            int base = dp1[u];
            int val = 1;
            int ylim = bucles[i] ? 1 : 0;
            for (int x = 0; x <= 1; x++) {
              for (int y = 0; y <= ylim; y++) {
                int cu = u + x + y;
                if (cu > max_ops_cad)
                  continue;
                int fi = val ^ x ^ y;
                int sig = bits[i + 1] ^ x;
                if (sig == 0) {
                  if (ndp0[cu] < base + fi)
                    ndp0[cu] = base + fi;
                } else {
                  if (ndp1[cu] < base + fi)
                    ndp1[cu] = base + fi;
                }
              }
            }
          }
        }
        dp0.swap(ndp0);
        dp1.swap(ndp1);
      }
    }
    // Update global DP with results from this group
    vector<int> nuevo(M + 1, NEG);
    for (int u = 0; u <= M; u++) {
      if (dp_global[u] == NEG)
        continue;
      for (int c = 0; c <= max_ops_cad && u + c <= M; c++) {
        if (mejor_cad[c] == NEG)
          continue;
        int v = dp_global[u] + mejor_cad[c];
        if (nuevo[u + c] < v)
          nuevo[u + c] = v;
      }
    }
    dp_global.swap(nuevo);
  }
  int mejor_fronteras = 0;
  // Find maximum achievable color segments
  for (int u = 0; u <= M; u++) {
    if (dp_global[u] > mejor_fronteras)
      mejor_fronteras = dp_global[u];
  }
  // Add 1 because number of segments = number of boundaries + 1
  cout << (mejor_fronteras + 1) << "\n";
  return 0;
}


// https://github.com/VaHiX/CodeForces/