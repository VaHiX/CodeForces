// Problem: CF 1766 C - Hamiltonian Wall
// https://codeforces.com/contest/1766/problem/C

/*
Purpose: Determine if a Hamiltonian path exists on a 2xM grid such that all black cells are visited exactly once, 
         and no white cells are visited. The path must follow adjacent cells (sharing a side) and must cover all black cells.

Algorithms/Techniques: 
- Recursive backtracking with memoization to explore valid paths
- Try starting from either row (0 or 1) and column 0
- At each step, decide whether to move right or potentially change rows (if the current column has no black cell in the other row)

Time Complexity: O(M), where M is the number of columns. Each cell is visited at most once due to the recursive structure.
Space Complexity: O(M), due to recursion stack depth in worst-case scenarios (linear recursion).
*/

#include <iostream>
#include <string>

using namespace std;
int n;
string s[2];

// Function to check if a valid Hamiltonian path exists starting from (i, j)
// Returns 1 if path exists, 0 otherwise
int g(int i, int j) {
  // Base case: reached end of column
  if (j == n)
    return 1;
  // If current cell is white, it's invalid
  if (s[i][j] != 'B')
    return 0;
  // If the other row at this column is also black, we must switch rows
  if (s[1 - i][j] == 'B')
    return g(1 - i, j + 1);
  // Otherwise, we continue in the same row
  return g(i, j + 1);
}

int main() {
  // Read number of columns
  for (cin >> n; cin >> n >> s[0] >> s[1];)
    // Try starting from both rows (0 and 1) and output YES if any path works
    cout << (g(0, 0) | g(1, 0) ? "YES" : "NO") << endl;
}


// https://github.com/VaHiX/CodeForces/