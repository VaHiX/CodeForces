// Problem: CF 1335 D - Anti-Sudoku
// https://codeforces.com/contest/1335/problem/D

/*
Purpose: This code solves the "Anti-Sudoku" problem by modifying at most 9 elements of a given correct Sudoku grid 
         to make it an "anti-sudoku", where each row, column, and 3x3 block contains at least two equal elements.

Algorithm:
- For each row in the Sudoku grid:
  - Iterate through each element of the row.
  - If the element is '1', change it to '2'.
- This ensures that we can modify at most 9 elements (one per row) to guarantee that each row has at least one duplicate.
- The solution works because changing one element in each row to a different value (like 1->2) 
  ensures at least one duplicate in each row and column when done correctly.
- The approach also ensures that 3x3 blocks are not disrupted too much to satisfy the anti-sudoku conditions.

Time Complexity: O(1) (since input is always 9x9 grid, it's constant time processing)
Space Complexity: O(1) (only using a fixed number of variables, no extra space required)
*/

#include <iostream>
#include <string>

int main() {
  long t; // Number of test cases
  std::cin >> t;
  while (t--) {
    for (long p = 0; p < 9; p++) { // Loop for all 9 rows
      std::string s;
      std::cin >> s; // Read the string representing the row
      for (long p = 0; p < 9; p++) { // Loop for all 9 columns in current row
        if (s[p] == '1') { // If the element is '1'
          s[p] = '2'; // Change it to '2'
        }
      }
      std::cout << s << std::endl; // Output modified row
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/