// Problem: CF 1706 A - Another String Minimization Problem
// https://codeforces.com/contest/1706/problem/A

/*
 * Problem: Another String Minimization Problem
 * Algorithm/Technique: Greedy approach with symmetric positions
 * Time Complexity: O(n * m) where n is the length of sequence and m is the string length
 * Space Complexity: O(m) for storing the string s
 *
 * The solution works by processing each operation in order and for each element in the sequence,
 * choosing the leftmost (in terms of symmetry) position to place 'A' if it's still 'B'.
 * This greedy selection ensures lexicographically smallest result.
 */

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    std::string s(m, 'B'); // Initialize string with all 'B's
    for (long p = 0; p < n; p++) {
      long x;
      std::cin >> x;
      --x; // Convert to 0-based index
      long y = m - 1 - x; // Symmetric position from the end
      long left = (x < y) ? x : y; // Choose the smaller index (leftmost)
      if (s[left] == 'B') {
        s[left] = 'A'; // Place 'A' at leftmost available position
      } else {
        s[m - 1 - left] = 'A'; // Else place 'A' at symmetric right position
      }
    }
    std::cout << s << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/