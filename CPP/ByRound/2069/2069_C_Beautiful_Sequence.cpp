// Problem: CF 2069 C - Beautiful Sequence
// https://codeforces.com/contest/2069/problem/C

/*
C. Beautiful Sequence

Algorithm: Dynamic Programming with State Tracking
Approach:
- For each element in the input array, we track three states:
  A: Number of valid subsequences ending at current position with last element = 1
  B: Number of valid subsequences ending at current position with last element = 2
  C: Number of valid subsequences ending at current position with last element = 3
- When processing a new element:
  If element is '1': increment A (extend all sequences by appending 1)
  If element is '2': extend B using previous A (since 2 can follow 1)
  If element is '3': extend C using previous B (since 3 can follow 2)
- This ensures we count only those subsequences that satisfy beautiful criteria:
    - Length >= 3
    - Each element (except first) has a smaller element to its left
    - Each element (except last) has a larger element to its right
Time Complexity: O(n) per test case
Space Complexity: O(1)
*/

#include <stdio.h>
#define M 998244353
int main() {
  int T, n, i;
  char s[2], x;
  unsigned int A, B, C;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (i = 0, A = B = C = 0; i < n; i++) {
      scanf("%s", s);           // Read next character
      x = s[0];                 // Extract the digit
      if (x == 50)              // If it's '2'
        B = ((B << 1) + A) % M; // Double B and add A to B (transition from 1 -> 2)
      else if (x == 49)         // If it's '1'
        A++;                    // Increment A (new valid start with 1)
      else                      // If it's '3'
        C = (C + B) % M;        // Add B to C (transition from 2 -> 3)
    }
    printf("%u\n", C);          // Print final result
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/