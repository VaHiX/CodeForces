// Problem: CF 1729 B - Decode String
// https://codeforces.com/contest/1729/problem/B

/*
B. Decode String
Algorithm: Greedy decoding from right to left.
  - Process the encoded string from right to left.
  - If a '0' is encountered, it indicates a two-digit number (from previous two digits).
  - Otherwise, single digit represents a letter.
Time Complexity: O(n) where n is the length of the encoded string.
Space Complexity: O(1) excluding output space.
*/
#include <iostream>
#include <string>
int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    std::string dec(""); // Resulting decoded string
    long idx(n - 1);     // Start from the last index
    while (idx >= 0) {
      long rank(0);       // Letter rank (1-26)
      if (s[idx] == '0') {
        // Two-digit number: extract previous two digits
        rank = 10 * (s[idx - 2] - '0') + (s[idx - 1] - '0');
        idx -= 3;  // Move back by three positions
      } else {
        // Single digit number
        rank = (s[idx] - '0');
        idx--;     // Move back by one position
      }
      char x = 'a' + rank - 1;  // Convert rank to character
      dec = x + dec;            // Prepend to result string
    }
    std::cout << dec << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/