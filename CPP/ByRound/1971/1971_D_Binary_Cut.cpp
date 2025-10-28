// Problem: CF 1971 D - Binary Cut
// https://codeforces.com/contest/1971/problem/D

/*
D. Binary Cut
Algorithm: Greedy approach to count transitions between '0' and '1'
Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1)

The problem asks for the minimum number of pieces to cut a binary string into such that 
the pieces can be rearranged to form a sorted binary string (all 0s followed by all 1s).

Key insight:
- We need to count how many times we transition from '0' to '1' and from '1' to '0'.
- Each transition of '0' -> '1' represents a "rise" that must be accounted for in the result.
- Each transition of '1' -> '0' represents a "drop" that also contributes to the number of pieces needed.
- The total number of pieces required is: 
    (number of '0'->'1' transitions) + (number of '1'->'0' transitions) + 1
    But since we only add 1 once, we compute (r - (r > 0) + d + 1)
*/

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long r(0), d(0); // r counts '0' to '1' transitions, d counts '1' to '0' transitions
    for (long p = 1; p < s.size(); p++) {
      r += (s[p - 1] == '0' && s[p] == '1'); // increment if we have a '0' followed by '1'
      d += (s[p - 1] == '1' && s[p] == '0'); // increment if we have a '1' followed by '0'
    }
    std::cout << (r - (r > 0) + d + 1) << std::endl; // Final formula for minimum pieces
  }
}


// https://github.com/VaHiX/codeForces/