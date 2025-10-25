// Problem: CF 1846 B - Rudolph and Tic-Tac-Toe
// https://codeforces.com/contest/1846/problem/B

/*
B. Rudolph and Tic-Tac-Toe
Time Complexity: O(1) per test case (since board size is fixed 3x3)
Space Complexity: O(1) (fixed-size array and variables)

Algorithm:
The code checks for winning conditions in a 3x3 tic-tac-toe game with three players (X, O, +).
It scans all possible lines (rows, columns, diagonals) to find if any player has formed a line of three identical symbols.
The check is done by iterating over all combinations of three positions (i, j, k) that form a line,
and verifying if they are equal and consecutive in a valid line pattern.

The nested loops iterate through every triplet of positions in the board such that:
- They represent a row/column/diagonal
- They are equally spaced to form a straight line
- Symbols at those positions are identical
If such a line is found, it returns that symbol; otherwise returns "DRAW"
*/

#include <iostream>
#include <string>

using namespace std;
char c[10]; // Array to store board state (1-based indexing for simplicity)

int main() {
  ios::sync_with_stdio(false), cin.tie(0); // Optimize I/O speed
  int t;
  cin >> t; // Read number of test cases
  while (t--) {
    string s = "DRAW"; // Default result is draw
    for (int i = 1; i <= 9; ++i)
      cin >> c[i]; // Read each character into 1-based array
    for (int i = 1; i <= 9; ++i) // Loop through all possible first positions
      for (int j = i + 1; j <= 9; ++j) // Loop through all possible second positions
        for (int k = j + 1; k <= 9; ++k) { // Loop through all possible third positions
          // Check if the three positions form a valid line:
          // - All are non-empty
          // - All have same symbol
          // - Equally spaced to form straight line (horizontal/vertical/diagonal)
          // - Special conditions on spacing to ignore invalid combinations
          if (c[i] != '.' && c[i] == c[j] && c[j] == c[k] && j - i == k - j &&
              (j - i != 2 || i == 3) &&
              (j - i != 1 || i == 1 || i == 4 || i == 7))
            s = c[i]; // Update result if a win is detected
        }
    cout << s << '\n'; // Output the result
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/