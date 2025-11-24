// Problem: CF 1423 A - Wakanda Forever
// https://codeforces.com/contest/1423/problem/A

/*
Algorithm: Stable Matching / Greedy Approach
Approach:
- This problem is about finding a stable pairing of cities such that no two cities would prefer to be paired with each other over their current partners.
- The algorithm works greedily:
  1. For each city, we find the city (say 'pos') which has the minimum cost to build a rail to the current city among all unpaired cities.
  2. We then check if 'pos' can be assigned to this city. If 'pos' is already paired, the assignment is invalid.
  3. Once we assign a city to another, we update any conflicting assignments.
- Time Complexity: O(N^3) due to nested loops for checking and updating.
- Space Complexity: O(N^2) for storing the cost matrix and O(N) for the answer array.

Techniques:
- Greedy assignment with conflict resolution.
- Pairing validation using minimum cost comparison.
*/

#include <stdio.h>
#include <iosfwd>

using namespace std;
const int N = 1005;
int n, a[N][N], ans[N];
int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &a[i][j]);
    }
  }
  for (int i = 0; i < n; i++) {
    ans[i] = -1;
  }
  for (int i = 0; i < n; i++) {
    int pos = -1;
    for (int j = 0; j < n; j++) {
      if (ans[j] == -1) {
        if (pos == -1) {
          pos = j;
        }
        continue;
      }
      if (a[j][i] < a[pos][i]) {
        pos = j;
      }
    }
    if (ans[pos] != -1) {
      printf("-1\n");
      return 0;
    }
    ans[pos] = i;
    for (int j = 0; j < n; j++) {
      if (ans[j] == -1) {
        continue;
      }
      if (a[pos][j] < a[pos][ans[j]]) {
        ans[j] = i;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    printf("%d\n", ans[i] + 1);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/