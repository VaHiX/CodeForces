// Problem: CF 946 C - String Transformation
// https://codeforces.com/contest/946/problem/C

/*
 * Problem: String Transformation
 * 
 * Purpose: Given a string of lowercase English letters, determine if it's possible
 *          to transform the string such that "abcdefghijklmnopqrstuvwxyz" appears
 *          as a subsequence. Each character can be replaced with the next character
 *          in the alphabet (e.g., 'a' -> 'b', 'z' -> impossible). 
 *          
 * Algorithm: Greedy approach
 *   - Iterate through the string from left to right.
 *   - For each position, if the current character is greater than or equal to
 *     the target character (starting from 'a'), replace it with the target character.
 *   - Increment the target character.
 *   - If the target character exceeds 'z', the transformation is complete.
 *   
 * Time Complexity: O(n) where n is the length of the string.
 * Space Complexity: O(1) as we modify the string in place and use only a constant amount of extra space.
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string s;
  std::cin >> s;
  char cur('a'); // Current target character, starting from 'a'
  for (long p = 0; p < s.size(); p++) {
    // If current character is already >= target character, skip it
    if (cur < s[p]) {
      continue;
    }
    // Replace current character with target and increment target
    s[p] = cur++;
    // If we've processed all letters from 'a' to 'z', stop
    if (cur > 'z') {
      break;
    }
  }
  // If we successfully transformed all letters, output the string, otherwise output "-1"
  std::cout << ((cur > 'z') ? s : "-1") << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/