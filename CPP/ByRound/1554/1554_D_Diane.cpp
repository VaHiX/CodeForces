// Problem: CF 1554 D - Diane
// https://codeforces.com/contest/1554/problem/D

/*
Purpose: This code generates a string of length n such that every non-empty substring appears an odd number of times.
         The approach uses a pattern of repeated 'a's with a specific ending to ensure the condition holds.

Algorithms/Techniques: 
- Greedy construction using repeated characters
- Special handling for odd and even lengths

Time Complexity: O(n) - Each test case takes linear time to construct the string.
Space Complexity: O(n) - Space required to store and output the string of length n.

*/

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    if (n == 1) {
      std::cout << "a" << std::endl;
      continue;
    }
    // Construct string with n/2 'a's, followed by 'bc' if n is odd, 'b' if even,
    // followed by (n/2 - 1) 'a's.
    std::cout << std::string(n / 2, 'a') + (n & 1 ? "bc" : "b") +
                     std::string(n / 2 - 1, 'a')
              << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/