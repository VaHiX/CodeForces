// Problem: CF 1965 C - Folding Strip
// https://codeforces.com/contest/1965/problem/C

/*
Purpose: This code computes the minimum possible length of a binary string strip after performing a valid set of folds. 
         A valid folding ensures that characters which end up on top of or below each other match.

Algorithms/Techniques: 
    - Simulation with direction tracking
    - Prefix sum-like approach using a counter to simulate folding
    - Efficient linear pass through the string

Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(1) additional space (excluding input storage)
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 2e5 + 10;
int T, n;
char s[N];
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    scanf("%s", s + 1);
    int l = 0, r = 0, now = 0, d = 1;
    for (int i = 2; i <= n; i++) {
      // If current character is same as previous, flip direction
      if (s[i] == s[i - 1])
        d = -d;
      else
        // Otherwise, move in current direction
        now += d;
      // Track minimum and maximum positions reached
      l = min(l, now);
      r = max(r, now);
    }
    // The difference between max and min positions + 1 gives the minimum length
    printf("%d\n", r - l + 1);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/