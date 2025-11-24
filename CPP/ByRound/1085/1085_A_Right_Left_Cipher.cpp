// Problem: CF 1085 A - Right-Left Cipher
// https://codeforces.com/contest/1085/problem/A

/*
 * Right-Left Cipher Decryption
 * 
 * Algorithm:
 *   - The encryption process builds a string by alternating between prepending and appending characters,
 *     starting with the first character, then appending the second, prepending the third, etc.
 *   - To decrypt, we reverse this process:
 *     1. Determine the length of the original string.
 *     2. Use a mathematical formula to map each encrypted character back to its original position.
 *     3. The mapping is based on alternating indices: for even positions in the result,
 *        we take from the left half; for odd positions in result, we take from right half.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

#include <stdio.h>

int i, n;
char p[51];
int main() {
  // Read input string
  for (scanf("%s", p); p[n]; n++)
    ; // Calculate length of the string
  // Decrypt and print the original string by reversing the encryption process
  for (; i++ < n;)
    putchar(p[(n - 1) / 2 + (i % 2 ? -i / 2 : i / 2)]);
}


// https://github.com/VaHiX/codeForces/