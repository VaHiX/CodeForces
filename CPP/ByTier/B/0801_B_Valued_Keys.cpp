// Problem: CF 801 B - Valued Keys
// https://codeforces.com/contest/801/problem/B

/*
Purpose: This program determines if there exists a string z such that f(x, z) = y,
where f(s1, s2) returns the lexicographically smaller character at each position
of the two input strings. If such a z exists, it is printed; otherwise, -1 is printed.

Algorithm:
- For each position i, check whether x[i] >= y[i]. If x[i] < y[i], it's impossible
  to find a z such that min(x[i], z[i]) = y[i], because the minimum of two characters
  can never be greater than either of them.
- If all positions satisfy x[i] >= y[i], then we can construct z = y (since
  min(x[i], y[i]) = y[i] when x[i] >= y[i]).

Time Complexity: O(n), where n is the length of the strings.
Space Complexity: O(n), for storing the string z.

Techniques:
- Greedy approach: If x[i] >= y[i], we can choose z[i] = y[i] to satisfy the condition.
- Early termination: If any character in x is smaller than the corresponding character in y,
  we immediately conclude no valid z exists.
*/

#include <iostream>
#include <string>

int main() {
  std::string x, y;
  std::cin >> x >> y;
  std::string z(y); // Initialize z with y, as this is a valid candidate if possible
  bool possible(true);
  
  // Check if for each position, x[i] >= y[i]
  for (long p = 0; p < x.size(); p++) {
    if (x[p] < y[p]) {
      possible = false; // Impossible to satisfy the condition
      break;
    }
  }
  
  std::cout << (possible ? z : "-1") << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/