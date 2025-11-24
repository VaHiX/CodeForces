// Problem: CF 1606 A - AB Balance
// https://codeforces.com/contest/1606/problem/A

/*
Code Purpose:
This solution aims to make the number of "ab" substrings equal to the number of "ba" substrings in a given string of 'a' and 'b' characters.
The key insight is that changing the first or last character can balance the counts efficiently.
If the first and last characters are different, we change the first to match the last.
This greedy approach minimizes the number of operations needed.

Algorithms/Techniques:
- Greedy algorithm
- String manipulation

Time Complexity: O(n) where n is the length of the string (due to input reading and output)
Space Complexity: O(n) for storing the string input

*/
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    if (s[0] != s.back()) {  // If first and last characters are different
      s[0] = s.back();  // Change first character to match last character
    }
    std::cout << s << std::endl;  // Output the modified string
  }
}


// https://github.com/VaHiX/CodeForces/