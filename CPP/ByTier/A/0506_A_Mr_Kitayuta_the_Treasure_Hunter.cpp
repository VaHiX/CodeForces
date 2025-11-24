// Problem: CF 506 A - Mr. Kitayuta, the Treasure Hunter
// https://codeforces.com/contest/506/problem/A

/*
Algorithm: Dynamic Programming with state tracking
Techniques: 2D Dynamic Programming with jump length tracking

Time Complexity: O(N * K) where N is the number of islands (30000) and K is the maximum jump length (500)
Space Complexity: O(N * K) for the DP table

The problem involves finding the maximum number of gems that can be collected by jumping
from island 0 to island d, then following specific jump rules where each jump length
can change by -1, 0, or +1 from the previous jump length.
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 30000;
int n, d, a[N + 5], p;
int f[N + 5][505], ans;

void work() {
  scanf("%d%d", &n, &d);
  // Read gem locations and store in array a
  for (int i = 1; i <= n; i++) {
    scanf("%d", &p);
    a[p]++;
  }
  // Initialize DP table with -1 (unreachable)
  memset(f, -1, sizeof(f));
  // First jump from 0 to d, set the initial state
  f[d][250] = a[d];
  // Iterate through all possible positions
  for (int i = d; i <= N; i++)
    // Iterate through all possible jump lengths (shifted by 250 to handle negative indices)
    for (int j = 1; j <= 500; j++)
      if (f[i][j] != -1) {
        // Update the answer with the maximum gems collected so far
        ans = max(ans, f[i][j]);
        // Calculate actual jump length from the shifted index
        int l = d + j - 250;
        // Jump of length l-1 if valid
        if (l > 1 && i + l - 1 <= N)
          f[i + l - 1][j - 1] =
              max(f[i + l - 1][j - 1], f[i][j] + a[i + l - 1]);
        // Jump of length l if valid
        if (i + l <= N)
          f[i + l][j] = max(f[i + l][j], f[i][j] + a[i + l]);
        // Jump of length l+1 if valid
        if (i + l + 1 <= N)
          f[i + l + 1][j + 1] =
              max(f[i + l + 1][j + 1], f[i][j] + a[i + l + 1]);
      }
  printf("%d\n", ans);
}

int main() {
  work();
  return 0;
}


// https://github.com/VaHiX/CodeForces/