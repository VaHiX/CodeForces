// Problem: CF 1744 A - Number Replacement
// https://codeforces.com/contest/1744/problem/A

/*
Problem: A. Number Replacement
Algorithm/Techniques: Hash mapping, greedy approach
Time Complexity: O(n) per test case, where n is the length of array a
Space Complexity: O(1) extra space (b array size is fixed at 52)

The task is to determine if we can transform an integer array into a given string
by replacing all occurrences of each number with a single letter. Each number maps
to exactly one letter, and each letter can only map to one number.

Approach:
1. For each test case, use a mapping array 'b' to store which letter each number maps to.
2. Iterate through the array and string simultaneously.
3. For each element:
   - If the number already has a mapped letter (b[a[i]] != 0):
     - Check if it matches the current letter s[i]
     - If not, return "NO"
   - Else:
     - Assign the current letter to b[a[i]]
4. If all elements match the mapping rules, return "YES"
*/

#include <cstring>
#include <stdio.h>
int main() {
  int t, n, f, i, a[52], b[52]; // b array tracks which letter each number maps to
  char s[51];
  scanf("%d", &t);
  while (t--) {
    memset(b, 0, sizeof(b)), scanf("%d", &n); // Reset mapping array and read n
    for (i = 0; i < n; ++i)
      scanf("%d", &a[i]); // Read the integer array
    scanf("%s", s); // Read the target string
    for (f = i = 0; i < n; ++i)
      b[a[i]] && b[a[i]] - s[i] ? f = 1 : b[a[i]] = s[i]; // Check and assign mappings
    puts(f ? "NO" : "YES"); // Output result
  }
}


// https://github.com/VaHiX/codeForces/