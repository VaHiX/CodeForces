// Problem: CF 1374 B - Multiply by 2, divide by 6
// https://codeforces.com/contest/1374/problem/B

/*
B. Multiply by 2, divide by 6
Algorithm: Analyze prime factorization of n
Time Complexity: O(log n) per test case
Space Complexity: O(1)

The problem asks to reduce a number n to 1 using two operations:
- multiply by 2
- divide by 6 (if divisible)

Key insights:
- Dividing by 6 is equivalent to dividing by 2 and 3
- Multiplying by 2 increases the power of 2 in factorization
- To reach 1, we must have only 2s and 3s in the prime factorization
- If there's any other prime factor, impossible
- The number of operations depends on how many 2s and 3s are present

Steps:
1. Factor out all 2s: count them as 'a'
2. Factor out all 3s: count them as 'b'
3. After removing 2s and 3s, if the result is not 1, impossible
4. If b < a, it's also impossible (we cannot "create" more 2s from 3s)
5. Minimum operations = 2 * b - a
   This is because:
   - We need 'b' operations to remove all 3s
   - Each 3 can be removed by one div by 6, but this also removes 2
   - So we need 2*b operations to remove all 3s (since each division by 6 removes a 2 as well)
   - But we had 'a' 2s originally; so net operations = 2*b - a
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long s(n), a(0), b(0);
    // Count how many times we can divide by 2
    while (s % 2 == 0) {
      ++a;
      s /= 2;
    }
    // Count how many times we can divide by 3
    while (s % 3 == 0) {
      ++b;
      s /= 3;
    }
    // If remaining number is not 1, or more 2s than 3s, impossible
    if (s != 1 || b < a) {
      puts("-1");
    } else {
      // Calculate minimum operations
      printf("%ld\n", 2 * b - a);
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/