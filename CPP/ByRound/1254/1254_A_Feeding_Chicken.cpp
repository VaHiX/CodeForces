// Problem: CF 1254 A - Feeding Chicken
// https://codeforces.com/contest/1254/problem/A

/*
Purpose: Assign farm cells to chickens such that each chicken gets a connected area and the difference between the maximum and minimum number of rice cells assigned to a chicken is minimized.

Algorithm:
1. Count total rice cells on the farm.
2. Determine how many cells each chicken should get (base count 'a' and extra count for first 'b' chickens).
3. Traverse the farm in a specific order (zig-zag pattern) to assign cells to chickens, ensuring connected areas.
4. Use a character mapping function to assign unique identifiers to chickens.

Time Complexity: O(r * c) per test case, where r and c are the dimensions of the farm.
Space Complexity: O(r * c) for storing the farm grid and intermediate results.

Techniques:
- Greedy assignment with zig-zag traversal to maintain connectivity.
- Character mapping for unique identifiers.
- Modular arithmetic to distribute rice cells evenly among chickens.
*/

#include <iostream>
#include <vector>
#include <string>

char getChar(int x) {
  if (x < 10) {
    return ('0' + x);  // Map 0-9 to '0'-'9'
  } else if (x < 36) {
    return ('a' + x - 10);  // Map 10-35 to 'a'-'z'
  } else if (x < 62) {
    return ('A' + x - 36);  // Map 36-61 to 'A'-'Z'
  } else
    return '#';  // Invalid case
}

int main() {
  int t;
  std::cin >> t;
  while (t--) {
    int r, c, k;
    std::cin >> r >> c >> k;
    std::vector<std::string> d(r);
    for (int row = 0; row < r; row++) {
      std::cin >> d[row];  // Read farm grid
    }
    std::vector<std::string> f(r);
    long total(0);
    for (int row = 0; row < r; row++) {
      for (int col = 0; col < c; col++) {
        total += (d[row][col] == 'R');  // Count total rice cells
      }
    }
    int a(total / k), b(total % k);  // Base count and extra count for first b chickens
    int cur(0);  // Current chicken index
    int g = a + (cur < b);  // Number of cells assigned to current chicken
    for (int row = 0; row < r; row++) {
      int start(0), stop(c), step(1);
      if (row % 2) {
        start = c - 1;  // For even rows, go left to right
        stop = -1;      // For odd rows, go right to left
        step = -1;
      }
      for (int col = start; col != stop; col += step) {
        bool rice = (d[row][col] == 'R');  // Check if the cell is rice
        d[row][col] = getChar(cur);        // Assign chicken identifier
        if (rice) {
          --g;
          if (g <= 0) {  // If current chicken's quota is met
            ++cur;
            if (cur >= k) {
              cur = k - 1;  // Clamp to last chicken
            };
            g = a + (cur < b);  // Reset quota for next chicken
          }
        }
      }
    }
    for (int row = 0; row < r; row++) {
      std::cout << d[row] << std::endl;  // Output result
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/