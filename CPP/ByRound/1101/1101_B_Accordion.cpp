// Problem: CF 1101 B - Accordion
// https://codeforces.com/contest/1101/problem/B

/*
B. Accordion
Purpose: Find the maximum length of an accordion that can be formed from the input string by removing characters.
An accordion is defined as [ : |* : ] where |* represents zero or more vertical bars.
Algorithm: 
    1. Locate the first '[' (ASCII 91) and move forward to find the first ':' after it.
    2. Locate the last ']' (ASCII 93) and move backward to find the first ':' before it.
    3. Verify that the structure is valid (first ':' comes before last ':').
    4. Count the number of '|' characters between these two colons.
    5. Return 4 + count of '|' characters if valid, else -1.

Time Complexity: O(n) where n is the length of input string
Space Complexity: O(1) excluding input storage

*/

#import <ios>
int i, s, x, y = 500000;
char p[500001];
int main() {
  for (scanf("%s", p); p[x] ^ 91 && p[x];) // Find first '[' character
    x++;
  for (; p[y] ^ 93 && y;) // Find last ']' character from end
    y--;
  for (; p[x] ^ 58 && p[x];) // Move forward to find first ':' after '['
    x++;
  for (; p[y] ^ 58 && y;) // Move backward to find last ':' before ']'
    y--;
  if (x >= y) { // Check if valid structure (first colon comes before last colon)
    puts("-1");
    return 0;
  }
  for (i = x; i < y; i++) // Count vertical bars between first and last colon
    s += p[i] == 124;
  printf("%d", s + 4); // Total length = 4 (for brackets and colons) + number of '|'
}


// https://github.com/VaHiX/codeForces/