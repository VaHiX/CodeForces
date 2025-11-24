// Problem: CF 1617 A - Forbidden Subsequence
// https://codeforces.com/contest/1617/problem/A

/*
Problem: A. Forbidden Subsequence
Purpose: Given a string S and a permutation T of "abc", find the lexicographically smallest permutation of S such that T is not a subsequence of the result.

Algorithms/Techniques:
- Count frequencies of characters 'a', 'b', 'c'
- Sort the input string to get a base lexicographical order
- If any of 'a', 'b', or 'c' is missing, output sorted string directly
- Otherwise:
  - Place all 'a's first
  - Place all 'c's next
  - Place all 'b's after that
  - Append remaining characters (greater than 'c') at the end

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the input string and temporary variables

Input Format:
- First line: number of test cases t
- For each test case:
  - Line 1: string S (length 1 to 100)
  - Line 2: string T (permutation of "abc")

Output Format:
- For each test case, output the lexicographically smallest permutation of S that does not contain T as a subsequence.
*/

#include <algorithm>
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s, u;
    std::cin >> s >> u;
    long a(0), b(0), c(0);
    for (long p = 0; p < s.size(); p++) {
      a += (s[p] == 'a'); // Count 'a'
      b += (s[p] == 'b'); // Count 'b'
      c += (s[p] == 'c'); // Count 'c'
    }
    sort(s.begin(), s.end()); // Sort input string lexicographically
    if (a == 0 || b == 0 || c == 0 || u != "abc") {
      std::cout << s << std::endl; // If any character missing or T is not "abc", output sorted string
      continue;
    }
    for (long p = 0; p < a; p++) {
      std::cout << "a"; // Place all 'a's first
    }
    for (long p = 0; p < c; p++) {
      std::cout << "c"; // Then all 'c's
    }
    for (long p = 0; p < b; p++) {
      std::cout << "b"; // Then all 'b's
    }
    for (long p = 0; p < s.size(); p++) {
      if (s[p] > 'c') { // Append remaining characters > 'c'
        std::cout << s[p];
      }
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/