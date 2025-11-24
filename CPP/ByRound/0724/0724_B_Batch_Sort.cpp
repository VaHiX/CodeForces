// Problem: CF 724 B - Batch Sort
// https://codeforces.com/contest/724/problem/B

/*
B. Batch Sort
Time Complexity: O(n * m^3 + m^4)
Space Complexity: O(n * m)

Algorithm:
- For each row, check if it's already in the correct order (1 to m).
- If any row has more than 2 misplaced elements, it's impossible to fix with one swap.
- Try all column pairs to swap and see if it makes any row valid.
- After swapping columns, try all possible swaps within each row to make it sorted.
- Use brute force for small constraints (n, m <= 20).

Techniques:
- Simulated Annealing / Brute Force
- Row-wise validation with early termination
- Column swap enumeration followed by row-wise correction
*/

#include <iostream>
#include <vector>
bool check(std::vector<std::vector<int>> f) {
  for (int row = 0; row < f.size(); row++) {
    int chg(0);
    for (int col = 0; col < f[row].size(); col++) {
      if (f[row][col] != col + 1) { // Check if element matches expected value at index
        ++chg;
      }
      if (chg > 2) { // Early termination: if more than 2 mismatches, it's impossible to fix with one row swap
        return false;
      }
    }
  }
  return true;
}
int main() {
  std::ios_base::sync_with_stdio(false);
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> mat(n, std::vector<int>(m, 0));
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < m; col++) {
      std::cin >> mat[row][col];
    }
  }
  bool possible = check(mat); // Check if it's already valid
  for (int p = 0; p < m; p++) { // Try swapping columns p and q
    if (possible) {
      break;
    }
    for (int q = p + 1; q < m; q++) {
      for (int row = 0; row < n; row++) {
        int tmp = mat[row][p]; // Perform swap
        mat[row][p] = mat[row][q];
        mat[row][q] = tmp;
      }
      possible = check(mat); // Check if this makes the matrix better
      if (possible) {
        break;
      }
      for (int row = 0; row < n; row++) {
        int tmp = mat[row][p]; // Revert swap
        mat[row][p] = mat[row][q];
        mat[row][q] = tmp;
      }
    }
  }
  std::cout << (possible ? "YES" : "NO") << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/