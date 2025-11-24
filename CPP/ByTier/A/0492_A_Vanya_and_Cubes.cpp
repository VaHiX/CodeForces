// Problem: CF 492 A - Vanya and Cubes
// https://codeforces.com/contest/492/problem/A

/*
Code Purpose: This program calculates the maximum height of a pyramid that can be built using n cubes,
where each level i contains 1+2+...+i cubes (triangular numbers).

Algorithm: Mathematical approach using the formula for triangular numbers.
The number of cubes needed for a pyramid of height h is: h*(h+1)*(h+2)/6
We find the maximum h such that h*(h+1)*(h+2)/6 <= n

Time Complexity: O(1) - The while loop runs a constant number of times (at most ~100),
since h*(h+1)*(h+2) grows rapidly and we're bounded by the input size.

Space Complexity: O(1) - Only using a constant amount of extra space.
*/

#include <iostream>

int main() {
  long n;
  std::cin >> n;
  long a = 0;
  // Loop until we find the first value where a*(a+1)*(a+2) > 6*n
  // This gives us the maximum height plus one, so we decrement a at the end
  while (a * (a + 1) * (a + 2) <= 6 * n) {
    ++a;
  };
  --a; // Adjust a to be the maximum valid height
  std::cout << a << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/