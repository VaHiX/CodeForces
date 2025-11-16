// Problem: CF 723 B - Text Document Analysis
// https://codeforces.com/contest/723/problem/B

/*
Algorithm/Techniques: Single Pass Parsing
Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) - only using a few variables for tracking state

The solution processes the string once from left to right, tracking:
- Whether we are currently inside parentheses (par)
- Whether we are currently forming a word (word)
- Current word length (len)
- Maximum word length outside parentheses (maxLen)
- Count of words inside parentheses (count)

The algorithm handles:
1. Parentheses: Changes the state of 'par' and resets word tracking
2. Letters: Increases current word length, increments count if inside parentheses
3. Underscores: Ends current word, updates maxLen if outside parentheses
*/

#include <iostream>
#include <string>

int main() {
  int n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  bool par(0), word(0);  // par: inside parentheses, word: currently forming a word
  int count(0), len(0), maxLen(0);
  for (int p = 0; p < s.size(); p++) {
    if (s[p] == '(') {
      // End of word outside parentheses, possibly update maxLen
      if (word == 1 && par == 0 && maxLen < len) {
        maxLen = len;
      }
      par = 1;  // Enter parentheses
      word = 0; // Reset word state
      len = 0;  // Reset length
    } else if (s[p] == ')') {
      par = 0;  // Exit parentheses
      word = 0; // Reset word state
      len = 0;  // Reset length
    } else if (('a' <= s[p] && s[p] <= 'z') || ('A' <= s[p] && s[p] <= 'Z')) {
      // Letter: extend current word
      if (word == 0) {
        count += par; // Increment count if inside parentheses
        len = 0;      // Reset length for new word
      }
      word = 1;  // We are now forming a word
      ++len;     // Increase word length
    } else if (s[p] == '_') {
      // Underscore: end of word
      if (word == 1 && par == 0 && maxLen < len) {
        maxLen = len;
      }
      word = 0; // Word ended
    }
  }
  // Handle the last word in case the string doesn't end with underscore or parenthesis
  if (word == 1 && par == 0 && maxLen < len) {
    maxLen = len;
  }
  std::cout << maxLen << " " << count << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/