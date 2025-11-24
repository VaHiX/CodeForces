// Problem: CF 1800 D - Remove Two Letters
// https://codeforces.com/contest/1800/problem/D

/*
D. Remove Two Letters
Purpose: For each test case, given a string of lowercase Latin letters, compute how many distinct strings can be obtained by removing exactly two consecutive characters.
Algorithm: 
  - For a string of length n, there are (n-1) possible consecutive pairs to remove.
  - We count how many unique strings we get after removing each pair.
  - Optimization:
    - Iterate through all positions of consecutive pairs.
    - For each removal, we create a new string by skipping two characters at position i and i+1.
    - However, we can optimize by observing that if s[i] == s[i+2], then removing s[i] and s[i+1] or s[i+1] and s[i+2] results in the same outcome.
    - The key trick: we subtract from (n-1) whenever two characters separated by one character are equal: i.e. when s[p] == s[p-2].
Time Complexity: O(n) per test case
Space Complexity: O(1) additional space (excluding input/output)
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
    long cnt(n - 1); // Initially, assume all pairs produce unique strings
    for (long p = 2; p < n; p++) {
      // If current character equals the one two positions back,
      // then removing s[p-1] and s[p] will give same result as removing s[p-2] and s[p-1]
      cnt -= (s[p] == s[p - 2]); // Decrease count if such duplicate exists
    }
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/