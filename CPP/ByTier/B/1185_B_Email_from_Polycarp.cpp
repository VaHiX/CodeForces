// Problem: CF 1185 B - Email from Polycarp
// https://codeforces.com/contest/1185/problem/B

/*
 * Problem: B. Email from Polycarp
 * Purpose: Determine if a string 't' could be a result of typing string 's'
 *          on a broken keyboard where pressing a key may produce multiple
 *          occurrences of that character.
 *
 * Algorithm:
 *   - Use two pointers approach to simulate the process:
 *     - Traverse through string 't'.
 *     - Match characters from 's' in order.
 *     - Allow repeated characters (from same key press) only if they are
 *       consecutive in 't'.
 *   - Time Complexity: O(|s| + |t|) for each pair, where |s| and |t| are the lengths of strings.
 *   - Space Complexity: O(1), excluding input storage.
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false); // Disable sync with C stdio for faster I/O
  long n;
  std::cin >> n;
  while (n--) {
    std::string s;
    std::cin >> s;
    std::string t;
    std::cin >> t;
    bool possible = true;
    long idx(0); // Pointer for string 's'
    for (long p = 0; p < t.size(); p++) {
      if (s[idx] == t[p]) {
        // Characters match, advance pointer in 's'
        ++idx;
      } else if (p > 0 && t[p] == t[p - 1]) {
        // Current character is same as previous one in 't',
        // so it could be a repeated press from the same key
      } else {
        // No match and not a repetition; impossible to form 's' from 't'
        possible = false;
        break;
      }
    }
    if (idx < s.size()) {
      // Not all characters of 's' were matched
      possible = false;
    }
    std::cout << (possible ? "YES" : "NO") << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/