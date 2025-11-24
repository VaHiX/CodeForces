// Problem: CF 1569 A - Balanced Substring
// https://codeforces.com/contest/1569/problem/A

/*
Algorithm/Technique: Greedy
Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) - only using a few variables regardless of input size

This solution looks for the first pair of adjacent characters that are different.
If such a pair is found, it returns the substring from the first character to the second character as a balanced substring,
since it will contain exactly one 'a' and one 'b' (or vice versa), making it balanced. If no such pair exists,
then it means the entire string consists of the same character, and thus no balanced substring exists.
*/
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long left(-1), right(-1);
    // Loop through adjacent characters to find a mismatch
    for (long p = 1; p < s.size(); p++) {
      if (s[p - 1] != s[p]) {
        left = p;           // Start index of the balanced substring (1-indexed)
        right = p + 1;      // End index of the balanced substring (1-indexed)
        break;
      }
    }
    std::cout << left << " " << right << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/