// Problem: CF 1902 A - Binary Imbalance
// https://codeforces.com/contest/1902/problem/A

/*
Problem: A. Binary Imbalance

Purpose:
This program determines whether it's possible to make the number of '0' characters in a binary string strictly greater than the number of '1' characters by performing a series of operations. Each operation inserts a character between two adjacent characters based on their equality.

Algorithms/Techniques:
- Simulates insertion logic by checking for transitions between different adjacent characters.
- A key observation is that inserting a '0' only happens when s[i] != s[i+1], and this can be used to increase the count of '0's.
- The solution reduces to checking if there exists at least one transition from '0' to '1' or from '1' to '0'. If both characters are same, then no '0' insertion can happen, otherwise there is a way to insert '0'.

Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(1), as only constant extra space is used.

Input Format:
- First line contains integer t (number of test cases).
- For each test case:
  - Line 1: integer n (length of string)
  - Line 2: string s of length n, containing only '0' and '1'

Output Format:
- For each test case: print "YES" if it's possible to have more zeros than ones, else "NO".
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false); // Optimize I/O speed
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    bool ans(false);
    for (long p = 0; !ans && p < n; p++) {
      if (s[p] == '0') { // If we find a '0', we can already have more zeros than ones
        ans = true;
      }
    }
    std::cout << (ans ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/