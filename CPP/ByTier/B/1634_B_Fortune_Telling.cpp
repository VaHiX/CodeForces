// Problem: CF 1634 B - Fortune Telling
// https://codeforces.com/contest/1634/problem/B

#include <cstdio>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, x, y;
    scanf("%lld %lld %lld", &n, &x, &y);
    ll v(0); // Count of odd numbers in the array
    while (n--) {
      long u;
      scanf("%ld", &u);
      v += (u % 2); // Add 1 if u is odd, 0 if even
      v %= 2;       // Keep only the parity (0 or 1)
    }
    // Determine who could reach y:
    // (x + v) % 2 == y % 2 means Alice can reach y
    // (x + 3 + v) % 2 == y % 2 means Bob can reach y
    // Since XOR with 3 flips bits, we use XOR to represent the difference
    if (((v ^ x) % 2) == (y % 2)) {
      puts("Alice");
    } else {
      puts("Bob");
    }
  }
}
/*
B. Fortune Telling

Purpose:
This code determines whether Alice or Bob can reach a specific final number y,
given their starting numbers x and x+3, respectively, and an array of operations.
Each operation on element ai allows either addition (d + ai) or XOR (d ^ ai).
The algorithm focuses on parity (even/odd nature) to simplify the problem.

Algorithms/Techniques:
- Bitwise XOR operations
- Parity analysis (counting odd numbers)
- Mathematical simplification using mod 2 arithmetic

Time Complexity: O(n), where n is the length of the array.
Space Complexity: O(1), only using a constant amount of extra space.
*/

// https://github.com/VaHiX/codeForces/