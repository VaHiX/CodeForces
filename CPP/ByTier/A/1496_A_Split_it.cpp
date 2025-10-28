// Problem: CF 1496 A - Split it!
// https://codeforces.com/contest/1496/problem/A

/*
Purpose: This program determines whether a given string can be split into k+1 parts such that
         the concatenation of these parts followed by the reverse of each part (in reverse order)
         forms the original string.

Algorithm:
- For each test case, we check if it's possible to form a valid decomposition by comparing
  characters from both ends of the string.
- We iterate through the string from both sides and count how many matching pairs exist
  at symmetric positions.
- If we find at least k such matching pairs, then it is possible to make the split.

Time Complexity: O(n) per test case where n is the length of the string.
Space Complexity: O(1) excluding input/output storage.

Techniques:
- Two-pointer technique for comparing characters from start and end
- Greedy approach to determine valid splits

*/

#include <iostream>
#include <stdio.h>
#include <string>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::string s;
    std::cin >> s;
    long idx(0); // Index to track matched symmetric pairs
    while (2 * idx + 2 < n && s[idx] == s[n - 1 - idx]) {
      ++idx; // Move forward if characters at symmetric positions match
    }
    puts(idx >= k ? "YES" : "NO"); // Output YES if enough matches found
  }
}


// https://github.com/VaHiX/codeForces/