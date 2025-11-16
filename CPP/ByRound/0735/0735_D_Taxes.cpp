// Problem: CF 735 D - Taxes
// https://codeforces.com/contest/735/problem/D

/*
Purpose: This code determines the minimum tax Mr. Funt has to pay by optimally splitting his income `n` into parts.
         The tax for each part is the largest proper divisor of that part.
         The goal is to minimize the total tax.

Algorithms/Techniques:
- Prime checking using trial division.
- Mathematical insight: 
  - If n is prime, tax = 1 (split into one part).
  - If n is even, tax = 2 (split into two parts of size 2 each).
  - If n is odd and n-2 is prime, tax = 2 (split into 2 and n-2).
  - Otherwise, tax = 3 (split into 3 parts, e.g., 2, 2, n-4 for odd n).

Time Complexity: O(sqrt(n)) due to the prime check.
Space Complexity: O(1) - only using a constant amount of extra space.
*/

#include <iostream>
long isPrime(long x) {
  if (x <= 1) {
    return false;
  }
  for (int p = 2; p * p <= x; p++) {
    if (x % p == 0) {
      return false;
    }
  }
  return true;
}
int main() {
  long n;
  std::cin >> n;
  long ans(0);
  if (isPrime(n)) {
    // If n is prime, we pay tax = 1 (no split needed)
    ans = 1;
  } else if (n % 2 == 0) {
    // If n is even, split into two parts of size 2 (tax = 2 + 2 = 4, but tax for each part is 1 each, so total = 2)
    ans = 2;
  } else if ((n % 2) && isPrime(n - 2)) {
    // If n is odd and n-2 is prime, split into 2 and n-2 (both >= 2, so valid)
    ans = 2;
  } else if ((n % 2) && !isPrime(n - 2)) {
    // If n is odd and n-2 is not prime, at least 3 parts are needed (e.g. 2, 2, n-4)
    ans = 3;
  }
  std::cout << ans << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/