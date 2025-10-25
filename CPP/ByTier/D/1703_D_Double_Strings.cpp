// Problem: CF 1703 D - Double Strings
// https://codeforces.com/contest/1703/problem/D

/*
D. Double Strings

Purpose:
This code determines for each string in a list whether it can be split into two strings from the same list such that the original string is their concatenation. 
It uses a set to store all input strings and checks all possible splits of each string.

Algorithms/Techniques:
- Hash set for O(1) average lookup time
- Brute-force enumeration of all valid splits (since string length <= 8)

Time Complexity: O(n * L^2)
Space Complexity: O(n * L) where L is the maximum length of the strings

Input:
- Number of test cases t
- For each test case:
  - Number of strings n
  - n strings of length at most 8

Output:
Binary string of length n, with 1 if string can be split into two others, else 0.
*/

#include <iostream>
#include <set>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::vector<std::string> v(n);
    std::set<std::string> f; // Set to store all input strings for fast lookup
    for (long p = 0; p < n; p++) {
      std::cin >> v[p];
      f.insert(v[p]); // Insert each string into the set
    }
    std::vector<int> res(n, 0); // Result array initialized to 0
    for (long p = 0; p < n; p++) {
      std::string cur = v[p]; // Current string being checked
      for (long len = 1; len < cur.size(); len++) {
        std::string x = cur.substr(0, len); // First part of split
        std::string y = cur.substr(len);    // Second part of split
        if (f.count(x) && f.count(y)) {     // If both parts exist in the set
          res[p] = 1;                       // Mark this string as valid
        }
        // Note: f.insert(cur) below is a bug - should not be here
      }
    }
    for (long p = 0; p < n; p++) {
      std::cout << res[p];
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/