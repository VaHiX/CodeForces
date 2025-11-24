// Problem: CF 961 C - Chessboard
// https://codeforces.com/contest/961/problem/C

/*
 * Code Purpose: 
 *   This program determines the minimum number of squares that need to be recolored 
 *   to form a valid chessboard from four n x n pieces. A valid chessboard has alternating 
 *   black and white squares such that no two adjacent squares (sharing a side) have the same color.
 *
 * Algorithm:
 *   1. For each of the 4 pieces, count how many squares are incorrectly colored.
 *      - A square at position (j, k) is considered correctly colored in a valid chessboard
 *        if it matches the expected color based on (j + k) % 2.
 *      - If (j + k) % 2 == 0, square should be black ('1'), otherwise white ('0').
 *   2. After counting errors for each piece, sort the counts.
 *   3. To minimize total recolorings, one of two scenarios is considered:
 *      - Either we fix the two pieces with the least errors and flip the two with the most errors.
 *        This is computed by summing the smaller two errors and subtracting larger two from 2*n^2.
 *   4. Output the minimal number of operations.
 *
 * Time Complexity:
 *   O(n^2) - We iterate through each of the 4 pieces of size n x n.
 *   Sorting 4 elements is constant time.
 *
 * Space Complexity:
 *   O(1) - We use only a fixed-size array (4 elements) and a few variables.
 */

#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  int n;
  cin >> n;
  int c1[4] = {}; // Array to store number of errors for each of the 4 pieces

  // Process each of the 4 pieces
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        char c;
        cin >> c;
        // If square (j,k) should be black (j+k is even) but is white (c == '0')
        // or should be white (j+k is odd) but is black (c == '1'), increment error count
        if (j % 2 == k % 2 && c == '0')
          c1[i]++;
        if (j % 2 != k % 2 && c == '1')
          c1[i]++;
      }
    }
  }

  // Sort error counts to determine min and max
  sort(c1, c1 + 4);

  // Minimum moves = errors in 2 smallest + (total squares - errors in 2 largest)
  cout << c1[0] + c1[1] + 2 * n * n - c1[2] - c1[3];
  return 0;
}


// https://github.com/VaHiX/CodeForces/