// Problem: CF 1676 C - Most Similar Words
// https://codeforces.com/contest/1676/problem/C

/*
C. Most Similar Words

Algorithm: Brute Force
- For each pair of words (i, j) where i < j, compute the Manhattan distance between them.
- The Manhattan distance is the sum of absolute differences of each character.
- Return the minimum such distance among all pairs.

Time Complexity: O(n^2 * m)
Space Complexity: O(n * m)

Input:
- t (number of test cases)
- For each test case:
  - n (number of words), m (length of each word)
  - n lines of strings of length m

Output:
- Minimum difference between any two strings
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    std::vector<std::string> v(n);
    for (long p = 0; p < n; p++) {
      std::cin >> v[p];
    }
    long mn(1e9); // Initialize minimum distance to a large value
    for (long p = 0; p < n; p++) {
      for (long q = p + 1; q < n; q++) {
        long dist(0); // Distance between current pair of strings
        for (long u = 0; u < m; u++) {
          long x = v[p][u] - v[q][u]; // Difference in ASCII values
          dist += (x < 0 ? -x : x);   // Take absolute value and add to distance
        }
        mn = (dist < mn) ? dist : mn; // Update minimum distance
      }
    }
    std::cout << mn << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/