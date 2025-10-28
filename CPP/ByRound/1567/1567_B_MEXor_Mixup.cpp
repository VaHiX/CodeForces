// Problem: CF 1567 B - MEXor Mixup
// https://codeforces.com/contest/1567/problem/B

/*
B. MEXor Mixup

This problem asks for the minimum length of an array such that:
- The MEX (Minimum Excluded) of the array is 'a'
- The XOR of all elements in the array is 'b'

Key insights:
1. For MEX to be 'a', the array must contain all integers from 0 to a-1, and at least one integer >= a.
2. To compute XOR efficiently for prefix operations, we use a helper function `computeXOR` that computes XOR from 0 to n.
3. The algorithm tries different lengths (1, 2, 3) based on properties of XOR and MEX constraints.

Time Complexity: O(1) per test case
Space Complexity: O(1)

Algorithms/Techniques:
- Prefix XOR optimization using modular arithmetic
- Greedy approach for minimal valid array length
*/

#include <cstdio>
long computeXOR(long n) {
  // Computes XOR of all numbers from 0 to n using pattern recognition
  if (n % 4 == 0) {
    return n;
  } else if (n % 4 == 1) {
    return 1;
  } else if (n % 4 == 2) {
    return n + 1;
  }
  return 0;
}
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    long x = computeXOR(a - 1); // XOR of all numbers from 0 to a-1
    long res(a + 2); // Default result initialization
    
    if (x == b) {
      res = a; // If prefix XOR equals target XOR, we need 'a' elements (0 to a-1)
    } else if ((x ^ b) != a) {
      res = a + 1; // Adjust based on mismatch between prefix XOR and target
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/