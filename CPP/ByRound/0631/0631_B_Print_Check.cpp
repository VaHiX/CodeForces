// Problem: CF 631 B - Print Check
// https://codeforces.com/contest/631/problem/B

/*
B. Print Check
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

Kris works in a large company "Blake Technologies". As a best engineer of the company he was assigned a task to develop a printer that will be able to print horizontal and vertical strips. First prototype is already built and Kris wants to tests it. He wants you to implement the program that checks the result of the printing.

Printer works with a rectangular sheet of paper of size n × m. Consider the list as a table consisting of n rows and m columns. Rows are numbered from top to bottom with integers from 1 to n, while columns are numbered from left to right with integers from 1 to m. Initially, all cells are painted in color 0.

Your program has to support two operations:
- Paint all cells in row r_i in color a_i;
- Paint all cells in column c_i in color a_i.

If during some operation i there is a cell that have already been painted, the color of this cell also changes to a_i.

Your program has to print the resulting table after k operations.

Algorithms/Techniques:
- For each row and column, track the last update time (rowNum, colNum) and color (rowColor, colColor)
- When querying a cell at (row, col), compare the last operation time on that row vs. column
- Time complexity: O(n * m + k)
- Space complexity: O(n + m)

Code:
*/

#include <iostream>
#include <vector>
int main() {
  std::ios_base::sync_with_stdio(false);
  long n, m, k;
  std::cin >> n >> m >> k;
  // rowNum[i] stores the last operation time for row i
  std::vector<long> rowNum(n, 0);
  // rowColor[i] stores the color of row i at its last operation
  std::vector<long> rowColor(n, 0);
  // colNum[i] stores the last operation time for column i
  std::vector<long> colNum(m, 0);
  // colColor[i] stores the color of column i at its last operation
  std::vector<long> colColor(m, 0);
  
  // Process k operations
  for (long p = 1; p <= k; p++) {
    long op, which, color;
    std::cin >> op >> which >> color;
    if (op == 1) {
      // Operation on row
      rowNum[which - 1] = p;
      rowColor[which - 1] = color;
    } else {
      // Operation on column
      colNum[which - 1] = p;
      colColor[which - 1] = color;
    }
  }
  
  // Generate output grid
  for (long row = 0; row < n; row++) {
    for (long col = 0; col < m; col++) {
      // Compare last operation time of row and column
      // The later one is the most recent update affecting cell (row, col)
      std::cout << ((rowNum[row] > colNum[col]) ? rowColor[row] : colColor[col])
                << " ";
    }
    std::cout << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/