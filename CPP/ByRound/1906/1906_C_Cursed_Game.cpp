// Problem: CF 1906 C - Cursed Game
// https://codeforces.com/contest/1906/problem/C

/*
 * Problem: Cursed Game
 * 
 * Description:
 * Solves a 3x3 grid puzzle where a secret paper with holes must be identified through
 * queries. Each query is an N x N grid of 0s and 1s. The demon compares the secret
 * paper (3x3 holes) with the query grid, shifting the secret paper to align with
 * each 3x3 region of the query. The result grid shows 1 if odd number of black cells
 * are visible through holes, 0 otherwise. Goal is to identify the secret configuration
 * (which cells have holes) by asking minimal queries within 999 total queries over 333 rounds.
 *
 * Approach:
 * - For N=3: Use random queries, since the grid is small and only one query is sufficient
 *   to determine the secret layout due to the small state space.
 * - For N>3: Use a deterministic approach:
 *   1. First query places black cell at (2,2) to detect a specific 3x3 region.
 *   2. Process the result grid to find the first 1, which corresponds to a region of
 *      the secret paper.
 *   3. Reconstruct the full layout of holes by inverting the process.
 *
 * Time Complexity: O(N^2) for each round, but bounded by total queries across 333 rounds.
 * Space Complexity: O(N^2) for storing grids and intermediate data.
 */

#include <assert.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>

using namespace std;
mt19937 mt(890694);
void solve() {
  auto read_grid = [&](int k) {
    vector<string> S(k);
    for (string &s : S)
      cin >> s;
    return S;
  };
  int N;
  cin >> N;
  if (N == 3) {
    // Special case for N=3: random queries work because
    // only one query is sufficient to identify the 3x3 secret layout.
    while (true) {
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          int c = mt() & 1;  // Randomly choose black or white
          cout << c;
        }
        cout << '\n';
      }
      cout << flush;
      string result;
      cin >> result;
      if (result == "CORRECT")
        return;
      read_grid(N - 2);  // Read the result grid (but we ignore it in this case)
    }
  } else {
    // For N > 3: build a query that allows us to isolate the hole location.
    vector<string> A(N, string(N, '0'));
    // Place a single black pixel in the center of the grid.
    for (int i = 0; i < N; i++) {
      A[2][2] = '1';
    }
    for (string s : A)
      cout << s << '\n';
    cout << flush;
    string result;
    cin >> result;
    if (result == "CORRECT")
      return;
    vector<string> res = read_grid(N - 2);  // Read the result grid after the first query.
    
    // Initialize the 3x3 grid to record where holes are.
    vector<string> B(3, string(3, '0'));
    pair<int, int> v;  // Store row, col of the first detected 1 in res.
    
    // Find the first 1 in the result grid (the first 3x3 region where holes were seen).
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        B[i][j] = res[i][j];
      }
    }
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (B[i][j] == '1') {
          v = {i, j};
          goto done;
        }
      }
    }
  done:;

    // Reconstruct the entire secret grid using the found location.
    vector<string> state(N - 2, string(N - 2, '1'));
    vector<string> G(N, string(N, '0'));
    
    // Use the identified region to reconstruct which positions in G should be black.
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        int li = i - 2 + v.first;
        int lj = j - 2 + v.second;
        if (li < 0 || lj < 0 || li >= N - 2 || lj >= N - 2)
          continue;
        if (state[li][lj] == '1') {
          G[i][j] = '1';
          for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
              if (B[x][y] == '1') {
                int ni = i - 2 + x;
                int nj = j - 2 + y;
                if (ni >= 0 && ni < N - 2 && nj >= 0 && nj < N - 2) {
                  state[ni][nj] ^= '0' ^ '1';  // Toggle the value for XOR.
                }
              }
            }
          }
          assert(state[li][lj] == '0');
        }
      }
    }
    assert(state == vector<string>(N - 2, string(N - 2, '0')));
    
    // Output final matrix to guess the hole positions.
    for (string x : G)
      cout << x << '\n';
    cout << flush;
    cin >> result;
    if (result == "CORRECT")
      return;
    assert(false);  // If we reach here, something went wrong.
  }
}
int main() {
  ios_base::sync_with_stdio(false), cin.tie(nullptr);
  int T = 333;
  while (T--)
    solve();
}


// https://github.com/VaHiX/CodeForces/