// Problem: CF 496 B - Secret Combination
// https://codeforces.com/contest/496/problem/B

/*
Purpose: Find the lexicographically smallest number that can be obtained by
         applying two operations on a circular digit string:
         1. Add 1 to all digits (with wraparound from 9 to 0)
         2. Shift all digits one position right (circular shift)
         The solution tries all possible combinations of these operations.

Algorithms/Techniques:
- Simulation of operations on a circular string
- Brute-force exploration of states (at most 10 shifts * n rotations)
- String comparison for finding minimum

Time Complexity: O(n * 10 * n) = O(n^2)
Space Complexity: O(n) for storing the string and substrings
*/

#include <cstdio>
#include <iostream>
#include <string>
int main() {
  int n;
  scanf("%d\n", &n);
  std::string comb;
  std::cin >> comb;
  comb += comb;  // Double the string to handle circular shifts easily
  std::string best = comb.substr(0, n);  // Initialize best with first substring
  for (int p = 0; p < 10; p++) {  // Try up to 10 additions (0 to 9)
    for (int d = 0; d < comb.size(); d++) {
      ++comb[d];  // Add 1 to digit
      if (comb[d] > '9') {
        comb[d] = '0';  // Wrap around from 9 to 0
      }
    }
    for (int s = 0; s < n; s++) {  // Try all rotations of the current state
      std::string current = comb.substr(s, n);
      if (current.compare(best) < 0) {  // Compare lexicographically
        best = current;  // Update best if current is smaller
      }
    }
  }
  std::cout << best << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/