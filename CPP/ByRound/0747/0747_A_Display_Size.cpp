// Problem: CF 747 A - Display Size
// https://codeforces.com/contest/747/problem/A

#include <iostream>
/*
Flowerbox:
Purpose: This program finds the optimal rectangular display dimensions (a rows, b columns) for exactly n pixels,
such that a <= b and the difference (b - a) is minimized.

Algorithm: 
- Start with initial values a = 1, b = n (1xN rectangle).
- Iterate through possible divisors p from 2 to sqrt(n).
- For each divisor p where n % p == 0:
  - Update a = p and b = n / p.
- Since we iterate from small to large p, the last valid pair (a, b) will have the smallest difference.

Time Complexity: O(sqrt(n)) because we iterate up to sqrt(n).
Space Complexity: O(1) as we use only a constant amount of extra space.
*/
int main() {
  long n;
  std::cin >> n;
  long a(1), b(n); // Initialize a=1 (min rows), b=n (max columns)
  for (long p = 2; p * p <= n; p++) { // Loop through potential divisors up to sqrt(n)
    if (n % p == 0) { // If p is a divisor of n
      a = p; // Update a to p
      b = n / p; // Update b to n/p
    }
  }
  std::cout << a << " " << b << std::endl; // Output the result
  return 0;
}


// https://github.com/VaHiX/CodeForces/