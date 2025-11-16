// Problem: CF 1753 C - Wish I Knew How to Sort
// https://codeforces.com/contest/1753/problem/C

/*
Code Purpose:
This code computes the expected number of operations needed to sort a binary array using a specific random swapping process.
It uses mathematical techniques to calculate the expected value based on the number of inversions and combinations of 0s and 1s in the array.

Algorithms:
- Combinatorial math to count inversions
- Modular exponentiation for computing modular inverse
- Efficient iteration through array elements

Time Complexity: O(n) per test case, where n is the size of the array.
Space Complexity: O(n) for storing the array elements.

Note: The algorithm efficiently calculates the expected number of operations in constant time,
      assuming the input is processed in linear time.
*/

#include <stdio.h>
#include <iostream>

long long n, T, a, c[1 << 22], y, r, o = 998244353, s, x;
int main() {
  for (std::cin >> T; T--; a = y = r = s = 0) {
    std::cin >> n;
    // Read array elements and count number of 0s
    for (; s < n; a += c[s] == 0)
      std::cin >> c[++s];
    // Count number of 1s
    for (s = 0; s < a;)
      y += c[++s] == 1;
    // Compute modular inverse using binary exponentiation
    for (; y; r += s)
      for (s = 1, a = o - 3, x = y--; a; a >>= 1, x = x * x % o)
        a & 1 ? s = s * x % o : 0;
    // Output result: (n*(n-1)/2) * r mod o
    printf("%d\n", n * (n - 1) / 2 % o * (r % o) % o);
  }
}


// https://github.com/VaHiX/CodeForces/