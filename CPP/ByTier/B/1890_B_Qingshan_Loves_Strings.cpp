// Problem: CF 1890 B - Qingshan Loves Strings
// https://codeforces.com/contest/1890/problem/B

/*
Algorithm/Techniques: String manipulation, checking for alternating patterns, 
                    and insertion strategy to make the string good.

Time Complexity: O(n + m) per test case, where n is length of s and m is length of t.
                 We traverse s and t at most a few times, each traversal is linear.

Space Complexity: O(1) extra space, not counting input storage.
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    std::string s, t;
    std::cin >> s >> t;
    bool res(true);
    
    // Check if s is already good (no two adjacent characters are equal)
    for (long p = 0; res && p + 1 < s.size(); p++) {
      if (s[p] == s[p + 1]) {
        res = false;
      }
    }
    
    // If s is already good, we can return YES immediately
    if (res) {
      std::cout << "YES" << std::endl;
      continue;
    }
    
    // Reset result flag
    res = true;
    
    // Check if t is good (no two adjacent characters are equal)
    for (long p = 1; res && p < t.size(); p++) {
      if (t[p] == t[p - 1]) {
        res = false;
      }
    }
    
    // If t is not good, we can't improve s by inserting t (since t itself is bad)
    if (!res) {
      std::cout << "NO" << std::endl;
      continue;
    }
    
    // If t has even length, there's no way to make s good by inserting it
    // because t is good but inserting an even-length good string cannot resolve all conflicts in s.
    if (t.size() % 2 == 0) {
      res = false;
    }
    
    // Check if it's possible to make s good by inserting t
    // If s has two adjacent equal characters, and that character differs from the first character of t,
    // we can possibly insert t in between to break the conflict.
    for (long p = 0; res && p + 1 < s.size(); p++) {
      if (s[p] != s[p + 1]) {
        continue;  // s[p] != s[p+1], not a conflict
      } else if (s[p] != t[0]) {
        continue;  // s[p] == s[p+1], but differs from t's first char; maybe a valid insertion
      } else {
        // s[p] == s[p+1] AND s[p] == t[0], impossible to insert t if we try to insert at this conflict.
        res = false;
      }
    }
    
    // Output final result
    std::cout << (res ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/