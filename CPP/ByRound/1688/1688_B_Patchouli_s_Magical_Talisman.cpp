// Problem: CF 1688 B - Patchouli's Magical Talisman
// https://codeforces.com/contest/1688/problem/B

/*
B. Patchouli's Magical Talisman
Purpose: Given a list of magical token powers (positive integers), determine the minimum number of operations to make all tokens have odd values.
Operations allowed:
1. Fusion: Choose two tokens and create a new token with their sum.
2. Reduction: Choose an even token and replace it with half its value.

Algorithm:
- For each test case:
  - Count how many odd numbers there are (`odds`).
  - For even numbers, count the minimum number of times we can divide by 2 until reaching an odd number (`minpow`).
  - If no odd numbers exist, we must reduce all even numbers to odd, but we can save one operation by fusing two of them.
  - Result is `evens + (odds == 0) * (minpow - 1)`.

Time Complexity: O(n) per test case, where n is the number of tokens.
Space Complexity: O(1), constant space usage.

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long odds(0), evens(0), minpow(1000); // Count odd numbers, even numbers, and minimum power of 2 dividing any even number
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x % 2) { // If x is odd
        ++odds;
      } else { // If x is even
        ++evens;
        long two(0); // Count how many times x can be divided by 2
        while (x % 2 == 0) {
          x /= 2;
          ++two;
        }
        minpow = (minpow < two) ? minpow : two; // Track the smallest power of 2 that divides any even number
      }
    }
    long res = evens + (odds == 0) * (minpow - 1); // Compute result based on odd/even counts and minimum reduction steps
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/