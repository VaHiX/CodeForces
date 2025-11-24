// Problem: CF 804 B - Minimum number of steps
// https://codeforces.com/contest/804/problem/B

/*
Purpose: 
  This code computes the minimum number of operations to transform a string of 'a' and 'b' 
  into a string where no 'ab' substring exists, by replacing 'ab' with 'bba'. 
  The approach uses a reverse scan to count how many 'b's are to the right of each 'a', 
  and calculates the total operations needed using dynamic counting and modular arithmetic.

Algorithms/Techniques:
  - Reverse iteration through the string
  - Dynamic counting of 'b's to the right of current position
  - Modular arithmetic to handle large numbers
  - Greedy approach with efficient state tracking

Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) - only using a constant amount of extra space
*/
#include <stdint.h>
#include <iostream>
#include <string>

int main() {
  const int64_t MOD = 1000000007;
  std::string s;
  std::cin >> s;
  int64_t count(0), total(0);
  for (int64_t p = s.size() - 1; p >= 0; p--) {
    if (s[p] == 'b') {
      count++;
      count %= MOD;
    } else {
      total += count;
      total %= MOD;
      count *= 2;
    }
  }
  std::cout << total << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/