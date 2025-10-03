// Problem: CF 2082 D - Balancing
// https://codeforces.com/contest/2082/problem/D

/*
D. Balancing
Algorithms/Techniques: Greedy approach with segment analysis
Time Complexity: O(n) per test case
Space Complexity: O(n)

The problem asks to make an array strictly increasing with minimum operations,
where each operation replaces a contiguous subarray while preserving the relative order.
We identify decreasing segments and process them greedily to minimize operations.

Key idea:
- Find all contiguous decreasing sequences (segments where a[i] > a[i+1])
- For each such segment, decide whether we need one or two operations to fix it
- Use greedy strategy based on how many operations are needed to maintain strict increase
*/

#include <stdio.h>
#include <iostream>

using namespace std;
const int maxn = 2e5 + 10;
int n, a[maxn];
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    int cnt = 0, st = 0, ed = 0;
    for (int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
    }
    for (int i = 2; i <= n; i++) {
      if (a[i] < a[i - 1]) { // Found a decreasing pair
        if (!st)
          st = i; // Mark start of the segment
        ed = i; // Extend end of segment
        cnt++;  // Count number of such pairs
      }
    }
    if (cnt == 0)
      puts("0"); // Already strictly increasing
    else if (cnt & 1)  
      printf("%d\n", (cnt + 1) / 2); // Odd count: we need exactly (cnt+1)/2 operations
    else if (a[ed] - a[st - 1] + 1 >= ed - st + 2) 
      printf("%d\n", cnt / 2); // Even count: check if we can use fewer operations
    else
      printf("%d\n", cnt / 2 + 1); // Otherwise one more operation is needed
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/