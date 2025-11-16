// Problem: CF 1579 A - Casimir's String Solitaire
// https://codeforces.com/contest/1579/problem/A

/*
Problem: A. Casimir's String Solitaire
Purpose: Determine if a string consisting of 'A', 'B', and 'C' can be completely erased by performing operations:
         1. Remove one 'A' and one 'B'
         2. Remove one 'B' and one 'C'
         Each operation reduces the string length by 2.
Algorithm: 
    - Count occurrences of each character ('A', 'B', 'C')
    - For a valid sequence, the number of 'B's must equal the sum of 'A's and 'C's
    - This ensures that all 'B's are paired with either 'A's or 'C's

Time Complexity: O(n), where n is the length of the string (single pass through string)
Space Complexity: O(1), only using a constant amount of extra space for counters

Input:
    t: number of test cases
    Each case contains a string s of length 1 to 50 consisting of 'A', 'B', 'C'
Output:
    YES if string can be fully erased, NO otherwise
*/
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long a(0), b(0), c(0);
    for (long p = 0; p < s.size(); p++) {
      a += (s[p] == 'A');  // Count 'A' characters
      b += (s[p] == 'B');  // Count 'B' characters  
      c += (s[p] == 'C');  // Count 'C' characters
    }
    std::cout << (b == a + c ? "YES" : "NO") << std::endl;  // Check condition for valid sequence
  }
}


// https://github.com/VaHiX/codeForces/