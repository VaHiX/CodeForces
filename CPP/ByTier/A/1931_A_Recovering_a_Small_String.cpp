// Problem: CF 1931 A - Recovering a Small String
// https://codeforces.com/contest/1931/problem/A

/*
 * Problem: Recovering a Small String
 * Description:
 *   Given an integer n (sum of positions of 3 lowercase letters), find the
 *   lexicographically smallest 3-letter word that encodes to n.
 * 
 * Approach:
 *   - Since we want the lexicographically smallest result, we try to minimize
 *     the first letter, then the second, and finally assign the third.
 *   - Start with the smallest possible value for the first character 'a' (position 1),
 *     but if even with 'a' the remaining sum is too large, increase it.
 *   - For remaining sum, apply same logic to second letter.
 *   - Third letter gets whatever's left.
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    // Assign first character to be as small as possible
    long a = (n > 52 ? (n - 52) : 1);  // Max value for 'z' is 26, so if n > 52, a must be at least n - 52; otherwise we can set a = 1
    n -= a;
    char x = 'a' + a - 1;  // Convert position to character
    // Assign second character to be as small as possible
    long b = (n > 26 ? (n - 26) : 1);  // Same logic for second char, max remaining n is 26, so if n > 26 then b needs to be at least n - 26; otherwise 1
    n -= b;
    char y = 'a' + b - 1;  // Convert position to character
    long c = n;            // Third character gets what's left
    char z = 'a' + c - 1;  // Convert position to character
    printf("%c%c%c\n", x, y, z);
  }
}


// https://github.com/VaHiX/codeForces/