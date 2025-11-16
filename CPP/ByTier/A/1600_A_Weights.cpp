// Problem: CF 1600 A - Weights
// https://codeforces.com/contest/1600/problem/A

/*
Code Purpose:
This code solves the problem of placing weights on a balance scale such that the sequence of
left (L) and right (R) heaviness conditions given by a string S are satisfied. The algorithm
uses a greedy approach: it sorts the weights and assigns them based on whether the current
condition is L or R, trying to satisfy the final requirement.

Algorithms/Techniques:
- Greedy algorithm with sorting
- Two-pointer technique

Time Complexity: O(N log N) due to sorting, where N is the number of weights.
Space Complexity: O(N) for storing the weights and answer array.

*/

#include <stdio.h>
#include <algorithm>

#define rgi register int
#define FOR(i, a, b) for (rgi i = a; i <= b; ++i)
using namespace std;
const int N = 400010;
int n, a[N], ans[N];
char s[N];
signed main() {
  scanf("%d", &n);
  FOR(i, 1, n) scanf("%d", &a[i]);
  sort(a + 1, a + n + 1), scanf("%s", s + 1);
  for (rgi l = 1, r = n; l <= r;) {
    rgi w = r - l + 1;
    if (s[w] == s[w - 1])
      ans[w] = l++;   // If the current instruction aligns with previous, take lighter weight from left
    else
      ans[w] = r--;   // Otherwise, take heavier weight from right
  }
  FOR(i, 1, n)
  printf("%d %c\n", a[ans[i]], "LR"[(ans[i] & 1) ^ (n & 1) ^ (s[n] == 'R')]);  // Output weight and side based on index and final string
  return 0;
}


// https://github.com/VaHiX/CodeForces/