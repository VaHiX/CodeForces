// Problem: CF 2125 A - Difficult Contest
// https://codeforces.com/contest/2125/problem/A

/*
 * Problem: A. Difficult Contest
 * Purpose: Rearrange the characters of a string to avoid "FFT" or "NTT" as substrings.
 * Approach:
 *   - Sort the string in descending order using reverse iterators.
 *   - This greedy strategy tries to place 'F' and 'N' at the beginning to prevent forming 
 *     forbidden patterns like "FFT" or "NTT".
 * Algorithms/Techniques: Sorting with reverse iterators.
 *
 * Time Complexity: O(n log n) per test case, where n is the length of the string,
 *                  due to sorting.
 * Space Complexity: O(n) for storing the input string and output.
 */

#include <algorithm>
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);  // Optimize I/O speed
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    sort(s.rbegin(), s.rend());  // Sort in descending order using reverse iterators
    std::cout << s << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/