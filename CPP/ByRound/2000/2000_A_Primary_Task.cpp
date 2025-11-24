// Problem: CF 2000 A - Primary Task
// https://codeforces.com/contest/2000/problem/A

/*
==================================================
Purpose: Determine if a given integer could have been written as 10^x (where x >= 2) 
         but without the '^' symbol, i.e., "10x" instead of "10^x".
         For example:
         - 10^2 = 100 → input "100"
         - 10^5 = 100000 → input "100000" (not in sample)
         - 10^3 = 1000 → input "1000"

Algorithm/Techniques:
- Check if the string representation of the number satisfies:
  1. Length > 2
  2. First two characters are '1' and '0'
  3. Third character is not '0'
  4. Not equal to "101" (since 10^1 = 10, we exclude x=1 case)

Time Complexity: O(1) per test case — constant time operations
Space Complexity: O(1) — only using a fixed amount of space for string processing
==================================================
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false); // Optimize I/O speed
  long t;
  std::cin >> t; // Read number of test cases
  while (t--) {
    std::string x;
    std::cin >> x; // Read the current number as string
    
    // Check conditions for valid "10^x" form:
    // 1. String length > 2
    // 2. First character is '1'
    // 3. Second character is '0'
    // 4. Third character is not '0'
    // 5. Not equal to "101" (to avoid x=1 case)
    bool res = (x.size() > 2) && (x[0] == '1') && (x[1] == '0') &&
               (x[2] != '0') && (x != "101");
    
    std::cout << (res ? "YES" : "NO") << std::endl; // Output result
  }
}


// https://github.com/VaHiX/codeForces/