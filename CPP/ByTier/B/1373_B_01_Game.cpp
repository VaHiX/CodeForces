// Problem: CF 1373 B - 01 Game
// https://codeforces.com/contest/1373/problem/B

/*
B. 01 Game
Purpose: Determine if Alice wins a game where players take turns removing two adjacent characters from a binary string.
Algorithm/Techniques: Counting zeros and ones, mathematical analysis of turn-based optimal play.
Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(1), only using a constant amount of extra space.

The key insight is that each move removes exactly 2 characters. 
If there are z zeros and a ones, the total number of moves possible is min(z, a).
Since Alice goes first, she wins if and only if min(z, a) % 2 == 1.
*/

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long z(0), a(0);
    for (long p = 0; p < s.size(); p++) {
      z += (s[p] == '0'); // Count zeros
      a += (s[p] == '1'); // Count ones
    }
    long x = (z < a) ? z : a; // Minimum of zeros and ones
    x %= 2; // If minimum is odd, Alice wins; else Bob wins
    std::cout << (x ? "DA" : "NET") << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/