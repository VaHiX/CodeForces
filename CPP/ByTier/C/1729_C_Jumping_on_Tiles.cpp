// Problem: CF 1729 C - Jumping on Tiles
// https://codeforces.com/contest/1729/problem/C

/*
Code Purpose:
This code solves the "Jumping on Tiles" problem where we need to find the optimal path from the first to the last tile of a string,
minimizing the total cost of jumps (based on letter index differences) while maximizing the number of jumps.

Approach:
1. For each character in the string, store its indices in a vector.
2. Determine the direction of traversal from the first character to the last character.
3. Traverse through all characters from the first to the last in the determined direction,
   appending indices of each character in order.
4. Output the total cost (based on direction and difference in character indices) and the sequence of indices.

Time Complexity: O(n) where n is the total number of characters across all test cases
Space Complexity: O(n) for storing indices of characters

Algorithms/Techniques:
- Greedy approach based on character index difference
- Preprocessing to map characters to their positions
- Linear traversal through character indices
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    std::vector<std::vector<long>> v(26); // Vector to store indices of each character (a-z)
    for (long p = 0; p < s.size(); p++) {
      v[s[p] - 'a'].push_back(p + 1); // Store 1-based index of each character
    }
    int step = s[0] < s.back() ? 1 : -1; // Determine traversal direction
    std::vector<long> seq; // Sequence of indices for the path
    for (long p = (s[0] - 'a'); p != (s.back() - 'a') + step; p += step) {
      for (long q = 0; q < v[p].size(); q++) {
        seq.push_back(v[p][q]); // Add all indices of current character to path
      }
    }
    std::cout << (step * (s.back() - s[0])) << " " << seq.size() << std::endl;
    for (long p = 0; p < seq.size(); p++) {
      std::cout << seq[p] << " "; // Output the sequence of indices
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/