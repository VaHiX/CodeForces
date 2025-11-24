// Problem: CF 1369 B - AccurateLee
// https://codeforces.com/contest/1369/problem/B

/*
B. AccurateLee
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Algorithm:
The problem asks to make a binary string "clean" by removing characters under specific conditions.
A move allows erasing one of two consecutive characters s[i] and s[i+1] if s[i] is '1' and s[i+1] is '0'.
The goal is to minimize the string length and produce the lexicographically smallest result.

Key insight:
- To minimize the string, we must remove all '1's that appear before any '0'.
- After removing those, we can't further reduce the string due to the constraints.
- The final answer will be: 
  - some '0's at the beginning (all the original '0's from start),
  - followed by '1's (all '1's at the end), 
  - but only such that we don't have leading '1's that can't be reduced.

We compute:
- z = number of leading zeros in string
- a = number of trailing ones in string
- Then if total non-leading zeros + non-trailing ones < n, i.e., if there are characters between leading zeros and trailing ones, we add one more zero to account for that.
- Output: z zeros, then a ones.

Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) (excluding input/output)

*/

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    std::cin >> n; // Read length of string
    std::string s;
    std::cin >> s; // Read binary string
    
    long z(0), a(0); // z counts leading zeros, a counts trailing ones
    
    // Count leading zeros
    for (long p = 0; p < n; p++) {
      if (s[p] == '0') {
        ++z;
      } else {
        break; // Stop at first non-zero
      }
    }
    
    // Count trailing ones
    for (long p = n - 1; p >= 0; p--) {
      if (s[p] == '1') {
        ++a;
      } else {
        break; // Stop at first non-one
      }
    }
    
    // Adjust z: if we have both leading zeros and trailing ones, 
    // then between them there must be some portion of the string which contributes one additional '0'
    z += (a + z < n);
    
    // Print the resulting string
    for (long p = 0; p < z; p++) {
      std::cout << '0'; // Print leading zeros
    }
    for (long p = 0; p < a; p++) {
      std::cout << '1'; // Print trailing ones
    }
    std::cout << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/