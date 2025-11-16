// Problem: CF 1927 B - Following the String
// https://codeforces.com/contest/1927/problem/B

/*
 * Problem: B. Following the String
 * 
 * Purpose: Reconstruct a string from its trace array, where each element a[i] represents 
 *          the number of previous occurrences of the character s[i] in the string.
 * 
 * Approach:
 * - Use a map to track the last used character for each occurrence count.
 * - For each position in the trace:
 *   - If a[i] == 0, assign the next available character (starting from 'a').
 *   - Otherwise, reuse the character that was used when the count was one less.
 * - Maintain a mapping of occurrence counts to characters to allow efficient lookup and updates.
 * 
 * Time Complexity: O(n log n) per test case due to map operations (insert, lookup, pop).
 * Space Complexity: O(n) for storing the result and the map.
 * 
 * Algorithms/Techniques:
 * - Hash map (std::map) for tracking character usage by occurrence count.
 * - Greedy character assignment.
 */

#include <iostream>
#include <map>
#include <vector>
int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::map<long, std::vector<long>> mv; // Map to store characters by occurrence count
    std::vector<char> res(n, ' ');        // Result string initialized with spaces
    char nxt('a');                        // Next available character to assign
    for (long p = 0; p < n; p++) {
      int x;
      std::cin >> x;
      char cur;
      if (x == 0) {
        // If no previous occurrence, assign the next available character
        cur = nxt;
        ++nxt;
      } else {
        // Reuse a character that was used for a[x-1] occurrences
        cur = mv[x - 1].back();
        mv[x - 1].pop_back();  // Remove the character since it's now used
      }
      std::cout << cur;
      mv[x].push_back(cur);    // Store the current character for future reference
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/