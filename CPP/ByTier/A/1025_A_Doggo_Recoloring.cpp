// Problem: CF 1025 A - Doggo Recoloring
// https://codeforces.com/contest/1025/problem/A

/*
 * Problem: A. Doggo Recoloring
 * Purpose: Determine if it's possible to make all puppies have the same color
 *          using a specific operation: choose a color that has at least two puppies,
 *          and recolor all of them to another color.
 * 
 * Algorithm/Techniques:
 * - Count frequency of each color (a-z)
 * - If any color appears more than once, we can perform an operation
 * - The key insight is that if there's at least one color with frequency > 1,
 *   we can gradually reduce the number of distinct colors until only one remains.
 * 
 * Time Complexity: O(n), where n is the length of the string. We iterate through
 *                  the string once to count frequencies, and then check up to 26
 *                  colors.
 * 
 * Space Complexity: O(1), since we use a fixed-size vector of size 26 for counting.
 */

#include <iostream>
#include <vector>
#include <string>

int main() {
  const int N = 26;                         // Number of possible colors (a-z)
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  std::vector<long> a(N, 0);                // Count frequency of each color
  for (long p = 0; p < s.size(); p++) {     // Count occurrences of each character
    ++a[s[p] - 'a'];
  }
  bool possible(s.size() <= 1);             // If only 0 or 1 puppy, already valid
  for (long p = 0; p < N; p++) {            // Check if any color occurs more than once
    if (a[p] > 1) {
      possible = true;
      break;
    }
  }
  std::cout << (possible ? "Yes" : "No") << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/