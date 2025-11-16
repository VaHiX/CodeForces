// Problem: CF 1602 A - Two Subsequences
// https://codeforces.com/contest/1602/problem/A

/*
Purpose: This code solves the problem of splitting a string into two non-empty subsequences,
         where the first subsequence 'a' is lexicographically smallest possible, and the
         second subsequence 'b' can be any valid string. The algorithm identifies the
         lexicographically smallest character and uses it as the first subsequence, then
         places all other characters in the second subsequence.

Algorithms/Techniques: 
- Greedy approach to find the minimum character in the string.
- Single pass to build the two subsequences.

Time Complexity: O(n), where n is the length of the input string. We iterate through the string twice.
Space Complexity: O(n), for storing the input string and the output strings.

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
    char mn('z');  // Initialize minimum character to 'z'
    long minPos(-1);  // Initialize position of minimum character
    for (long p = 0; p < s.size(); p++) {
      if (s[p] <= mn) {  // If current character is less than or equal to current min
        mn = s[p];  // Update minimum character
        minPos = p;  // Update position of minimum character
      }
    }
    std::string a(1, mn), b("");  // a is initialized with the minimum character
    for (long p = 0; p < s.size(); p++) {
      if (p == minPos) {  // Skip the minimum character's position
        continue;
      }
      b = b + s[p];  // Append remaining characters to b
    }
    std::cout << a << " " << b << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/