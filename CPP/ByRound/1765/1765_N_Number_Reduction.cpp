// Problem: CF 1765 N - Number Reduction
// https://codeforces.com/contest/1765/problem/N

/*
N. Number Reduction
Algorithms/Techniques: Monotonic Stack, Greedy
Time Complexity: O(n) where n is the length of the input string x
Space Complexity: O(n) for the stack and auxiliary arrays

The problem is to remove exactly k digits from a number such that the remaining number is minimized.
This is solved using a greedy algorithm with a monotonic stack:
- We iterate through each digit and maintain a stack of digits
- For each new digit, if it's smaller than the top of the stack and we still have removals left,
  we pop from the stack (greedily removing larger digits)
- We also keep track of the last non-zero digit to ensure no leading zeros are created
- After processing all digits, we remove any remaining k digits from the end

*/

#include <cstdio>
#include <cstring>
const int o = 5e5 + 10;
int T, n, k, tp, pre[o], lst;
char x[o], st[o];
int main() {
  for (scanf("%d", &T); T--; putchar('\n')) {          // Process each test case
    scanf("%s%d", x + 1, &k);                         // Read input number and k
    n = strlen(x + 1);                                // Get length of number
    st[lst = tp = 1] = x[1];                          // Initialize stack with first digit
    for (int i = 2; i <= n; ++i) {                    // Iterate through remaining digits
      for (;                                           // While we can remove digits and conditions are met:
           tp && x[i] < st[lst] &&                     // Current digit is smaller than top of stack
           (lst > 1 || x[i] > 48) &&                   // Not removing leading zero unless it's not the first non-zero
           k >= tp - lst + 1;)                         // We still have enough removals left
        k -= tp - lst + 1, tp = lst - 1, lst = pre[lst]; // Remove digits and update pointers
      st[++tp] = x[i];                                  // Add current digit to stack
      pre[tp] = lst;                                    // Save previous pointer
      if (st[tp] > '0')                                 // If current digit is non-zero
        lst = tp;                                       // Update last non-zero position
    }
    for (int i = 1; i <= tp - k; ++i)                   // Output final number after k removals
      putchar(st[i]);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/