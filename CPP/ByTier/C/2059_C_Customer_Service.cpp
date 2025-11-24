// Problem: CF 2059 C - Customer Service
// https://codeforces.com/contest/2059/problem/C

/*
C. Customer Service

Algorithm: Greedy + Sorting
Time Complexity: O(n^2 log n)
Space Complexity: O(n^2)

The problem involves managing n queues over n time steps. At each time step:
- New customers arrive in all queues (given by input matrix a[i][j])
- Exactly one queue is served (its count becomes 0)

Goal: Maximize the MEX of final queue sizes.

Approach:
1. For each queue i, calculate when it can be served last so that its final size is minimized.
   This is done by finding the rightmost position where a[i][j] != 1 (i.e., where we don't have to serve this queue early).
2. Sort these "last possible times" in ascending order.
3. Greedily assign services: if the j-th service time allows us to achieve MEX >= j, increment the answer.

Key insight:
We want to delay serving queues as long as possible without violating constraints.
So for each queue, determine the latest it could be served, then sort and use greedy assignment.
*/

#include <algorithm>
#include <stdio.h>
using namespace std;
int n, a[303][303], t[303];

void solve() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      scanf("%d", &a[i][j]);
  
  // For each queue, compute the latest time it can be served
  for (int i = 1; i <= n; i++) {
    for (int j = n; j >= 0; j--) {
      if (a[i][j] != 1) { // If we don't have to serve this queue right now
        t[i] = n - j;     // How many time steps to skip before serving it
        break;
      }
    }
  }

  sort(t + 1, t + n + 1);     // Sort the times in ascending order

  int ans = 1;
  for (int i = 1; i <= n; i++) {
    if (t[i] >= ans) {       // If this queue can be served at time >= ans
      ans++;                 // Increment desired MEX
    }
  }
  
  printf("%d\n", min(ans, n)); // MEX cannot exceed n
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--)
    solve();
}


// https://github.com/VaHiX/codeForces/