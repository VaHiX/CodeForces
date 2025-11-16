// Problem: CF 1775 A2 - Gardener and the Capybaras (hard version)
// https://codeforces.com/contest/1775/problem/A2

/*
Purpose: This code solves the problem of splitting a binary string (composed of 'a' and 'b') 
         into three parts representing names of capybaras such that either:
         - a <= b and c <= b (b is the maximum), or 
         - b <= a and b <= c (b is the minimum).
         It outputs any valid split satisfying the condition.
         
Algorithms/Techniques: Greedy approach with string splitting based on first and last character comparisons.

Time Complexity: O(n), where n is the length of the string due to single pass and substring operations.
Space Complexity: O(n), for storing the input string and the three output substrings.

The solution assumes that a valid split exists and is found greedily:
1. If first and last characters are equal: take first as 'a', middle as 'b', last as 'a' 
   or first as 'b', middle as 'b', last as 'b'.
2. If second character is 'a': take first as 'a', second as 'a', rest as third.
3. Else (second char is 'b'): similar to first case but adjust accordingly.
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    std::string x(""), y(""), z("");
    // Check if first and last characters are the same to form a valid split
    if (s[0] == s.back()) {
      x = s[0];  // First part is the first character
      y = s.substr(1, s.size() - 2);  // Middle part is everything except first and last
      z = s.back();  // Third part is the last character
    } else if (s[1] == 'a') {
      // If second character is 'a', make first part first char, second part second char,
      // and third part everything else
      x = s[0];
      y = s[1];
      z = s.substr(2, s.size() - 2);
    } else {
      // For cases where second character is not 'a', use similar logic
      x = s[0];
      y = s.substr(1, s.size() - 2);
      z = s.back();
    }
    std::cout << x << " " << y << " " << z << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/