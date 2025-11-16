// Problem: CF 1626 B - Minor Reduction
// https://codeforces.com/contest/1626/problem/B

/*
B. Minor Reduction
Algorithm: Greedily find the first pair of adjacent digits whose sum is >= 10,
           replace them with their sum (split into digits if needed) to maximize
           the result. If no such pair exists, simply add the first two digits
           and keep the rest.

Time Complexity: O(n) where n is the length of the string
Space Complexity: O(n) for storing the string

*/

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    bool done(false);
    // Traverse from right to left to find first adjacent pair with sum > 9
    for (long p = s.size() - 1; p >= 1; p--) {
      long sum = s[p - 1] - '0' + s[p] - '0';
      if (sum > 9) {
        // Replace the two digits with their sum split into two digits
        s[p - 1] = ('0' + sum / 10);
        s[p] = ('0' + sum % 10);
        done = true;
        break;
      }
    }
    if (done) {
      // If we found a valid pair, output the modified string
      std::cout << s << std::endl;
      continue;
    }
    // If no valid pair found, just add first two digits and append rest
    std::cout << ((char)(s[0] + s[1] - '0'));
    for (long p = 2; p < s.size(); p++) {
      std::cout << s[p];
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/