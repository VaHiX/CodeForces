// Problem: CF 860 A - Did you mean...
// https://codeforces.com/contest/860/problem/A

/*
 * Problem: Beroffice text editor typo detection and correction
 * 
 * Algorithm: Sliding window approach to detect blocks of 3 or more consonants
 *            that contain at least 2 different letters. When such a block is found,
 *            insert spaces to break it into smaller valid segments.
 * 
 * Time Complexity: O(n) where n is the length of the input string
 * Space Complexity: O(n) for storing the result string
 * 
 * Techniques:
 * - Character classification (vowels vs consonants)
 * - Greedy space insertion at appropriate positions
 * - Linear scan with lookahead to detect problematic sequences
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  string s;
  cin >> s;
  // Lambda function to check if a character is a consonant
  auto isa = [](char c) {
    vector<char> g = {'a', 'e', 'u', 'i', 'o', ' '}; // List of vowels + space
    for (char t : g) {
      if (c == t)
        return false; // If character is a vowel, return false (not a consonant)
    }
    return true; // Otherwise it's a consonant
  };
  string ans = "";
  ans += s[0]; // Add first character
  if (s.size() > 1)
    ans += s[1]; // Add second character
  int n = s.size();
  for (int i = 2; i < n; ++i) {
    int w = ans.size();
    // Check if last two characters in ans and current character form a typo
    if (isa(ans[w - 2]) and isa(ans[w - 1]) and isa(s[i])) {
      // If all three are consonants and at least two are different
      if (ans[w - 1] != ans[w - 2] or s[i] != ans[w - 1])
        ans += ' '; // Insert space to break the typo
    }
    ans += s[i]; // Add current character
  }
  cout << ans << '\n';
}


// https://github.com/VaHiX/CodeForces/