// Problem: CF 1279 C - Stack of Presents
// https://codeforces.com/contest/1279/problem/C

/*
C. Stack of Presents
Algorithm: Simulation with optimal reordering
Time Complexity: O(n + m) per test case
Space Complexity: O(n) for the array KK

Santa sends presents from a stack in order given by list b.
For each present, he must remove all above it, take it (1 second),
and then reorder the removed presents optimally before putting them back.
Total time for taking a present at position k (counting from 0)
is 2*k + 1 seconds. We track the positions of elements in the stack
using an array KK and simulate the process with optimal reordering.

Key idea:
- For each present in list b, we find its current position in the stack.
- If it's below or at the current index (i), no need to move anything.
- Else, we must move all between current position and previous index,
  which adds 2*(new_index - old_index) to total time.
*/
#include <stdio.h>
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int KK[100000]; // Array to store position of each present in the stack
    int n, m, h, i;
    long long ans;
    scanf("%d%d", &n, &m);
    for (i = 0; i < n; i++) {
      int a;
      scanf("%d", &a);
      KK[a - 1] = i; // Store index of present 'a' in stack (0-based)
    }
    ans = m; // Start with time for taking m presents (1 second each)
    i = -1;  // Current topmost index in the stack
    for (h = 0; h < m; h++) {
      int a;
      scanf("%d", &a);
      if (i < KK[a - 1]) { // If current present is below or at the top
        i = KK[a - 1];    // Update the new top of stack
        ans += (i - h) * 2; // Add cost of moving presents above it
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/