// Problem: CF 1766 B - Notepad#
// https://codeforces.com/contest/1766/problem/B

#include <iostream>
#include <set>
#include <string>
int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    std::set<std::string> dc;  // Set to store all previously seen substrings of length 2
    bool res(false);
    std::string last("");  // Keep track of the last visited substring of length 2
    for (long p = 0; !res && p + 1 < s.size(); p++) {
      std::string u = s.substr(p, 2);  // Extract a substring of 2 characters
      if (dc.count(u) && last != u) {  // If we've seen this substr before and it's not the same as last
        res = true;  // Found a duplicate, which means we can reuse it via copy-paste
      } else {
        dc.insert(u);  // Insert current substring into set
        last = (last != u) ? u : "";  // Update last substring, but avoid setting it if it's the same
      }
    }
    std::cout << (res ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/