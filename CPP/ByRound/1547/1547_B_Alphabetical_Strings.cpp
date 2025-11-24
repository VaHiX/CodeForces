// Problem: CF 1547 B - Alphabetical Strings
// https://codeforces.com/contest/1547/problem/B

/*
B. Alphabetical Strings
Algorithms/Techniques: Two-pointer approach, simulation of string construction
Time Complexity: O(n) per test case, where n is the length of the string
Space Complexity: O(1) additional space (not counting input storage)

The problem asks to determine if a given string can be constructed by repeatedly 
appending or prepending letters 'a' through 'z' in order. The key insight is that 
an alphabetical string must maintain a contiguous sequence of letters from 'a' 
in the final string, with each subsequent letter either prepended or appended.

Approach:
1. First locate the position of 'a' in the input string.
2. From there, simulate the process of building the string by checking if 
   each next letter ('b', 'c', ...) appears at one of the ends (left or right).
3. If all letters from 'a' to the last letter are found in order at the ends, 
   then it's an alphabetical string.
*/

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long left(-1), right(-1);
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == 'a') { // Find first occurrence of 'a'
        left = right = p;
        break;
      }
    }
    bool possible(left >= 0); // If 'a' was found, we can proceed
    for (long p = 1; possible && p < s.size(); p++) {
      char x = 'a' + p; // Current expected character ('b', 'c', ...)
      if (left > 0 && s[left - 1] == x) { // Check if x is at the left end
        --left;
      } else if (right + 1 < s.size() && s[right + 1] == x) { // Check if x is at the right end
        ++right;
      } else {
        possible = false; // No valid position for x found
      }
    }
    std::cout << (possible ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/