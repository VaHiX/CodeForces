// Problem: CF 2155 B - Abraham's Great Escape
// https://codeforces.com/contest/2155/problem/B

/*
B. Abraham's Great Escape
Problem Description:
Given an n x n grid and a number k, we need to assign directions (U, D, L, R) to each cell such that exactly k starting positions allow Abraham to escape the maze by following the arrows.

Approach:
- If k is 0 or equals n^2, we can easily make all cells point inward or all outward.
- For other values of k, we try to place k cells pointing outward in a way that maximizes escape points without overcounting.
- The idea is to set the first K cells to 'U' (up) so they escape immediately if they are at the top edge.
- After setting those K steps, fill rest with appropriate directions (R, D, L) to ensure correct behavior.

Time Complexity: O(N^2) per test case due to filling the grid.
Space Complexity: O(N^2) for storing the grid.

Algorithms/Techniques:
- Greedy assignment of arrow directions
- Grid traversal and conditional logic

*/

#include <iostream>

using namespace std;
#define ll long long
#define f first
#define s second
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int N, K, wyk = 0; // wyk keeps track of how many cells have been assigned the escape move 'U'
    cin >> N >> K;
    if (N * N < K || K == N * N - 1) { // Impossible cases: not enough space or only one non-escape cell
      cout << "NO\n";
      continue;
    }
    cout << "YES\n";
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (wyk < K) { // If we still have moves to assign as escape cells
          wyk++; // increment escape counter
          cout << "U"; // set escape direction
        } else {
          if (i != N - 1) // if not on last row
            cout << "D";
          else { // if on last row
            if (j == N - 1)
              cout << "L"; // corner case: last row, last column -> 'L'
            else
              cout << "R"; // otherwise -> 'R'
          }
        }
        if (j == N - 1)
          cout << "\n";
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/