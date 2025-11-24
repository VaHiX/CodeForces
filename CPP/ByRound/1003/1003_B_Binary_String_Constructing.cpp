// Problem: CF 1003 B - Binary String Constructing
// https://codeforces.com/contest/1003/problem/B

/*
 * Binary String Constructing
 * 
 * Algorithm/Technique:
 *   - Construct a binary string with exactly 'a' zeros and 'b' ones,
 *     such that there are exactly 'x' transitions between different
 *     adjacent characters.
 *   - Strategy:
 *     1. Determine which digit (0 or 1) is more frequent.
 *     2. Alternate between the two digits 'x' times to create transitions.
 *     3. Append the remaining digits of the more frequent type.
 *     4. Append the remaining digits of the less frequent type.
 * 
 * Time Complexity: O(a + b)
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long d[2], x; // d[0] = a (zeros), d[1] = b (ones), x = number of transitions
  scanf("%ld %ld %ld", d, d + 1, &x);
  int flag(d[1] >= d[0] ? 0 : 1); // Determine which digit is more frequent
  while (x > 0) {
    flag = 1 - flag; // Toggle the flag to switch between 0 and 1
    printf("%d", flag); // Print current digit
    --x; // Decrease transition count
    --d[flag]; // Decrease remaining count of current digit
  }
  while (d[flag]) { // Print remaining digits of the current type
    printf("%d", flag);
    --d[flag];
  }
  flag = 1 - flag; // Switch to the other digit type
  while (d[flag]) { // Print remaining digits of the other type
    printf("%d", flag);
    --d[flag];
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/