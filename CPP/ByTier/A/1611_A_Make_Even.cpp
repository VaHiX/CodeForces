// Problem: CF 1611 A - Make Even
// https://codeforces.com/contest/1611/problem/A

/*
Problem: A. Make Even
Purpose: Given a number without digit 0, determine the minimum number of prefix reversals needed to make it even.
Algorithms/Techniques: 
    - Greedy approach with analysis of parity and position of even digits
    - Simulation of operations based on digit positions
    
Time Complexity: O(n) where n is the length of the string representation of the number (linear scan)
Space Complexity: O(n) for storing the string input

The key idea:
- If last digit is even, no operations needed (0)
- If last digit is odd and first digit is even, one operation to move even digit to last position (1)
- If last digit is odd and first digit is odd, check if any even digit exists:
    - If yes, one operation to bring it to the end (1)
    - If no, impossible (-1)
- If no even digits at all, impossible (-1)

*/
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    std::string ans("2"); // Default answer
    bool has(false); // Flag to check if any even digit exists
    for (long p = 0; p < s.size(); p++) {
      if ((s[p] - '0') % 2 == 0) { // Check if digit is even
        has = true; // Set flag if even digit found
        break;
      }
    }
    if (!has) {
      ans = "-1"; // No even digit exists, impossible
    } else if ((s.back() - '0') % 2 == 0) { // Last digit is even
      ans = "0"; // Already even
    } else if ((s[0] - '0') % 2 == 0) { // First digit is even but last is odd
      ans = "1"; // One operation to move even digit to end
    } else {
      ans = "2"; // First digit odd, last odd, needs at least two operations
    }
    std::cout << ans << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/