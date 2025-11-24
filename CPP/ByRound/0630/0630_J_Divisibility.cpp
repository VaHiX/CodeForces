// Problem: CF 630 J - Divisibility
// https://codeforces.com/contest/630/problem/J

/*
Purpose: This code determines how many numbers from 1 to n are divisible by all integers from 2 to 10.
Algorithm: 
- Find the least common multiple (LCM) of numbers 2 through 10
- The LCM of 2,3,4,5,6,7,8,9,10 is 2^3 * 3^2 * 5 * 7 = 2520
- Count how many multiples of this LCM exist in range [1,n] by computing n / LCM
Time Complexity: O(1) - constant time operation
Space Complexity: O(1) - constant space usage
*/
#include <stdint.h>
#include <iostream>

int main() {
  // Calculate LCM of numbers 2 through 10: 2^3 * 3^2 * 5 * 7 = 2520
  const int64_t D = (2 * 2 * 2) * (3 * 3) * 5 * 7;
  int64_t n;
  std::cin >> n;
  // Count multiples of LCM in range [1,n]
  std::cout << (n / D) << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/