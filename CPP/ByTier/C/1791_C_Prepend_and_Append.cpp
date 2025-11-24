// Problem: CF 1791 C - Prepend and Append
// https://codeforces.com/contest/1791/problem/C

/*
C. Prepend and Append
Problem: Given a binary string, determine the shortest possible length of the original string that could have been transformed into it by prepending a '0' and appending a '1', or vice versa.

Algorithm:
- Two pointers approach to find the longest prefix and suffix that match.
- The key insight is that we can remove matching characters from both ends as long as they are different.
- The result is the remaining length of the string after removing such pairs.

Time Complexity: O(n) where n is the length of the string, since we scan the string once with two pointers.
Space Complexity: O(1), only using a constant amount of extra space.

*/
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false); // Disable synchronization with C stdio for faster input/output
  long t;
  std::cin >> t; // Read number of test cases
  while (t--) {
    long n;
    std::cin >> n; // Read length of the string
    std::string s;
    std::cin >> s; // Read the binary string
    long left(0), right(s.size() - 1); // Initialize two pointers at start and end of string
    
    // Move pointers inward while characters at both ends are different
    while ((left < right) && (s[left] != s[right])) {
      ++left;   // Move left pointer forward
      --right;  // Move right pointer backward
    }
    
    // The remaining length is the answer
    std::cout << (right - left + 1) << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/