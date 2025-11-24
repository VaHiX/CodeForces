// Problem: CF 1203 E - Boxers
// https://codeforces.com/contest/1203/problem/E

/*
E. Boxers
Algorithm: Greedy + Frequency Counting
Time Complexity: O(n + max_weight)
Space Complexity: O(max_weight)

The problem asks to find the maximum number of boxers that can form a team where all weights are distinct,
and each boxer can adjust their weight by at most 1 (weight must remain positive).

Approach:
- Count frequency of each weight using an array `tong`.
- Greedily assign available weights to boxers:
  - For each weight i, if there's a boxer with that weight, we can use it.
  - Otherwise, greedily try to assign the next available weight (i+1) or previous (i-1),
    and mark them as used so they aren't reused.
*/

#include <cstdio>
int n, a[150010], tong[150010], ans;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), tong[a[i]]++; // Read weights and count frequencies
  for (int i = 1; i <= 150001; i++)
    tong[i - 1] ? ans++                   // If weight i-1 has a boxer, use it
                : (tong[i]   ? ans++,     // Else if current weight i is available, use it and reduce count
                   tong[i]-- :            // Decrement the count for next match
                   (tong[i + 1] ? ans++, tong[i + 1]-- : 1)); // Else try weight i+1, else skip this slot
  printf("%d\n", ans);
}


// https://github.com/VaHiX/codeForces/