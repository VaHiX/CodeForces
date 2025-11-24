// Problem: CF 1230 B - Ania and Minimizing
// https://codeforces.com/contest/1230/problem/B

/*
B. Ania and Minimizing
Algorithm: Greedy approach to minimize the number by changing at most k digits.
Approach:
1. If k is 0, no changes allowed, output original string.
2. If string length is 1, change it to '0' if it's not already '0'.
3. Otherwise:
   - First, try to make the first digit '1' (to avoid leading zero).
   - Then, iterate through the rest of the digits from left to right.
   - For each digit that is not '0', change it to '0' (greedy to minimize).
   - Stop when k operations are exhausted or all digits processed.

Time Complexity: O(n) where n is the length of string s
Space Complexity: O(1) excluding the input string

*/
#include <iostream>
#include <string>

int main() {
  long n, k;
  std::cin >> n >> k;
  std::string s;
  std::cin >> s;
  if (k == 0) {
    std::cout << s << std::endl;
  } else if (s.size() == 1) {
    std::cout << "0" << std::endl;
  } else {
    if (s[0] != '1') {
      s[0] = '1';  // Change first digit to '1' to avoid leading zero
      --k;         // Decrement k as we used one operation
    }
    for (long p = 1; p < s.size() && k > 0; p++) {
      if (s[p] == '0') {
        continue;  // Skip if already '0'
      }
      s[p] = '0';   // Change digit to '0' to minimize
      --k;          // Decrement k as we used one operation
    }
    std::cout << s << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/