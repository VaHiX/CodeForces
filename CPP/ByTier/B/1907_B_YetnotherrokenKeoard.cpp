// Problem: CF 1907 B - YetnotherrokenKeoard
// https://codeforces.com/contest/1907/problem/B

/*
 * Problem: Yet Another Broken Keyboard
 * 
 * Purpose:
 *   Simulates a broken keyboard where pressing 'b' deletes the last lowercase letter
 *   and pressing 'B' deletes the last uppercase letter from the typed string.
 *   The letters 'b' and 'B' themselves are not added to the string.
 *
 * Algorithm:
 *   - Use two stacks (vectors) to track indices of lowercase and uppercase letters.
 *   - Process each character in the input string:
 *     * If 'b': delete last lowercase letter (pop from smalls vector)
 *     * If 'B': delete last uppercase letter (pop from caps vector)
 *     * If lowercase letter: push index onto smalls
 *     * If uppercase letter: push index onto caps
 *   - Mark characters to be shown using a boolean vector.
 *   - Output remaining characters in order.
 *
 * Time Complexity: O(n), where n is the length of the input string (each character processed once).
 * Space Complexity: O(n), for storing indices and the boolean show vector.
 */

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    std::vector<long> smalls, caps;           // Stack to store indices of lowercase and uppercase letters
    std::vector<bool> show(s.size(), true);   // Boolean vector to mark which characters to show
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == 'b') {
        show[p] = false;                      // Mark 'b' as not shown
        if (smalls.size() == 0) {             // If no lowercase letters, ignore
          continue;
        }
        show[smalls.back()] = false;          // Mark last lowercase letter to be hidden
        smalls.pop_back();                    // Remove from stack
      } else if (s[p] == 'B') {
        show[p] = false;                      // Mark 'B' as not shown
        if (caps.size() == 0) {               // If no uppercase letters, ignore
          continue;
        }
        show[caps.back()] = false;            // Mark last uppercase letter to be hidden
        caps.pop_back();                      // Remove from stack
      } else if (s[p] >= 'a' && s[p] <= 'z') {
        smalls.push_back(p);                  // Push lowercase letter index
      } else if (s[p] >= 'A' && s[p] <= 'Z') {
        caps.push_back(p);                    // Push uppercase letter index
      }
    }
    for (long p = 0; p < s.size(); p++) {
      if (show[p]) {                        // If character is marked to be shown
        std::cout << s[p];
      }
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/