// Problem: CF 689 A - Mike and Cellphone
// https://codeforces.com/contest/689/problem/A

/*
Code Purpose:
This program determines whether a given phone number can be uniquely identified
based on the finger movements used to input it. It checks if there exists another
number that would produce the same sequence of finger movements on a standard phone keypad.

Algorithm:
- Each digit on the keypad is mapped to a bitmask representing its position.
- For each digit in the input, we compute a bitwise AND of all the masks.
- If the result is non-zero, it means there's at least one other digit that could
  produce the same movement vector, indicating ambiguity.
- If the result is zero, then no other number produces the same movements, so the
  number is unique.

Time Complexity: O(n)
Space Complexity: O(1)

The keypad layout is:
    1 2 3
    4 5 6
    7 8 9
    * 0 #

Each digit has an associated bitmask (example for each digit from 0-9):
0 -> 15 (binary: 1111)
1 -> 8  (binary: 1000)
2 -> 6  (binary: 0110)
3 -> 7  (binary: 0111)
4 -> 14 (binary: 1110)
5 -> 15 (binary: 1111)
6 -> 11 (binary: 1011)
7 -> 12 (binary: 1100)
8 -> 15 (binary: 1111)
9 -> 9  (binary: 1001)

The 'op' array stores these bitmasks for digits 0 through 9.
*/
#include <cstdio>

const int op[10] = {8, 6, 7, 3, 14, 15, 11, 12, 15, 9}; // Bitmasks for each digit
int n, ans;
char s[555];
int main() {
  scanf("%d%s", &n, s);
  ans = 15; // Start with full bitmask (all bits set)
  for (int i = 0; i < n; i++)
    ans &= op[s[i] - '0']; // Bitwise AND of all digit masks
  printf("%s\n", ans ? "NO" : "YES"); // If result is non-zero, not unique
  return 0;
}


// https://github.com/VaHiX/CodeForces/