// Problem: CF 1384 A - Common Prefixes
// https://codeforces.com/contest/1384/problem/A

/*
 * Problem: Common Prefixes
 * 
 * Algorithm/Technique: Greedy string construction
 * 
 * Time Complexity: O(n^2) per test case, where n is the number of elements in array a.
 *                    This is due to string operations (copying and modifying) in the loop.
 * 
 * Space Complexity: O(n) for the string storage, and O(1) extra space per test case.
 * 
 * Approach:
 * - Initialize a base string filled with 'a' characters.
 * - For each prefix length 'a_i' in the input array:
 *   - Modify the character at position 'a_i' to be either 'b' or 'a', depending on current value,
 *     to ensure that the prefix of the current string matches the required length.
 *   - Output this modified string.
 * 
 * This method ensures that successive strings differ at the required prefix length,
 * which guarantees that the longest common prefix between consecutive strings equals
 * the corresponding element in the array a.
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    // Initialize a long string of 'a's to start with
    std::string s(200, 'a');
    // Output the first string
    std::cout << s << std::endl;
    for (long p = 0; p < n; p++) {
      long pos(0);
      std::cin >> pos;
      // Modify the character at 'pos' to ensure prefix condition is met
      s[pos] = (s[pos] == 'a') ? 'b' : 'a';
      std::cout << s << std::endl;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/