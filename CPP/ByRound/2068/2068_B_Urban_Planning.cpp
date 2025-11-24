// Problem: CF 2068 B - Urban Planning
// https://codeforces.com/contest/2068/problem/B

/*
B. Urban Planning
Purpose: Generate a grid with exactly k rectangular walks.
Algorithms/Techniques: 
- Greedily build a grid by placing parks (#) and adjusting layout to match exactly k rectangular walks.
- Uses combinatorics and mathematical adjustments to control the number of valid rectangles formed.
Time Complexity: O(N^2 + N*M + M^3), where N=2025, M=30. Dominated by initialization and loops.
Space Complexity: O(N*N), for storing the grid.

Rectangular Walk:
- A rectangle at least 2x2 in size such that all its boundary cells are parks(#).
- The number of such walks can be controlled by strategically placing # and . characters.

Approach:
- Start with a grid fully filled with #.
- Subtract total count of possible rectangles from k until it's less than or equal to k.
- Apply several refinement techniques to precisely match the required k value.
- Add # regions in a structured way using mathematical patterns based on k remaining.

Note: The solution uses fixed-size grid (2025x2025) and is designed to fit within given memory constraints.
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using i64 = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  i64 k;
  cin >> k;
  constexpr int N = 2025; // Grid size
  constexpr int M = 30;   // Small adjustment area size
  vector<string> ans(N, string(N, '#')); // Initialize full grid with parks
  i64 tot = 1LL * N * (N - 1) / 2 * N * (N - 1) / 2; // Total possible rectangular walks in full grid

  // Step 1: Fill small part of the grid with dots to reduce total count
  for (int i = 0; i <= M; i++) {
    for (int j = 0; j <= M; j++) {
      tot -= (N - 1 - i) * (N - 1 - j); // Subtract contributions of current dot area
      ans[i][j] = '.'; // Mark this cell as built-up area
    }
  }

  int lastx = -1, lasty = -1;
  // Step 2: Iterate through grid and adjust to match k more precisely
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (ans[i][j] == '#' && tot > k) {
        tot -= (N - 1 - i) * (N - 1 - j); // Reduce count when removing a # cell
        ans[i][j] = '.'; // Change to built-up
        lastx = i;
        lasty = j;
      }
    }
  }

  // Step 3: Fine-tune the solution using helper function for adjustments near edges
  auto work = [&](int x, int y) {
    while (tot < k - N) { // If still far from target k
      int len = 0;
      while (tot + 1LL * len * (len + 1) / 2 * (N - 1 - x) <= k) {
        len++; // Increase the region until we get close to k
      }
      tot += 1LL * len * (len - 1) / 2 * (N - 1 - x); // Update total count
      y--; // Move up
      for (int i = 0; i < len; i++) {
        ans[x][y--] = '#'; // Fill area with parks
      }
    }
  };

  // Apply refinement based on position of last modification
  if (lasty > 300) {
    work(lastx, lasty);
  } else {
    work(lastx - 1, N - 1); // Use alternative edge adjustment
  }

  // Step 4: Adjust what's left using more mathematical structure
  k -= tot; // Remaining difference from k

  int curx = 0, cury = 0;

  // Use blocks of large rectangles to reduce k gradually
  while (k >= M * (M - 1) / 2) {
    int len = 2;
    while (len * (len + 1) / 2 * M * (M - 1) / 2 <= k) {
      len++; // Find appropriate block size
    }
    for (int i = 0; i < len; i++) {
      for (int j = 0; j < M; j++) {
        ans[curx + i][cury + j] = '#'; // Place park block
      }
    }
    k -= len * (len - 1) / 2 * M * (M - 1) / 2; // Deduct from k
    curx += len + 1; // Move to next area
  }

  // Step 5: Final fine-tuning using small adjustments
  while (k) {
    int len = 2;
    while (len * (len + 1) / 2 <= k) {
      len++;
    }
    if (cury + len > M) { // Move row if necessary
      curx += 3;
      cury = 0;
    }
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < len; j++) {
        ans[curx + i][cury + j] = '#'; // Fill last small region
      }
    }
    k -= len * (len - 1) / 2; // Deduct from k
    cury += len + 1; // Go to next column
  }

  cout << N << " " << N << "\n"; // Output grid dimensions
  for (int i = 0; i < N; i++) {
    cout << ans[i] << "\n"; // Print the grid line by line
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/