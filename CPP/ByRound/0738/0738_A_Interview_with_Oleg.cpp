// Problem: CF 738 A - Interview with Oleg
// https://codeforces.com/contest/738/problem/A

// Task: Replace all maximal filler words (starting with 'ogo' and followed by
// any number of 'go') with '***'. Algorithm:
// - Use regular expression to match the pattern "ogo(go)*" which represents all
// valid filler words.
// - Replace each matched filler with "***".
// Time Complexity: O(n), where n is the length of the string, as regex matching
// and replacement is linear. Space Complexity: O(n), for storing the input
// string and the result string.

#include <iostream>
#include <regex>
#include <string>
using namespace std;

int main() {
  int n;
  cin >> n;
  string s;
  cin >> s;
  regex regex("ogo(go)*"); // Pattern to match all valid filler words
  cout << regex_replace(s, regex, "***")
       << endl; // Replace all matches with "***"
  return 0;
}

// https://github.com/VaHiX/CodeForces/