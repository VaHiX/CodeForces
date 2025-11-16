// Problem: CF 1067 A - Array Without Local Maximums 
// https://codeforces.com/contest/1067/problem/A

/*
 * Problem: A. Array Without Local Maximums
 * Algorithm: Dynamic Programming with States
 * Time Complexity: O(n * 200) = O(n)
 * Space Complexity: O(n * 200) = O(n)
 *
 * The task is to count the number of ways to fill the array such that:
 * - a[1] <= a[2]
 * - a[n] <= a[n-1]
 * - for all i from 2 to n-1: a[i] <= max(a[i-1], a[i+1])
 *
 * We use dynamic programming with states f[i][t] = number of valid ways
 * to fill first i elements such that a[i] = t and the prefix satisfies the condition.
 *
 * g[i][t] tracks the sum of f[i][t'] + g[i][t'] for t' < t, which helps in maintaining
 * cumulative sums needed for the transition involving the constraint:
 * a[i] <= max(a[i-1], a[i+1]).
 */

#include <stdio.h>
#include <tuple>

using namespace std;
typedef long long ll;
const int MOD = 998244353;
int f[100005][201];
int g[100005][201];

void add(int &a, int b) {
  a += b;
  if (a >= MOD)
    a -= MOD;
}

int main() {
  int n;
  ignore = scanf("%d", &n);
  f[0][1] = 1; // Base case: empty prefix, start with value 1
  for (int i = 1; i <= n; i++) {
    int a;
    ignore = scanf("%d", &a);
    int s1 = 0;
    // Iterate backwards to compute f[i][t] and accumulate sum of f[i-1][t'] for t' >= t
    for (int t = 200; t >= 1; t--) {
      add(s1, f[i - 1][t]);
      if (a == -1 || a == t) { // Only compute if current value matches or can be anything
        f[i][t] = s1; // f[i][t] = sum of f[i-1][t'], t' >= t
        add(f[i][t], g[i - 1][t]); // Add contribution from g[i-1][t]
      }
    }
    int s2 = 0;
    // Iterate forward to compute g[i][t] and accumulate sum of f[i-1][t'] + g[i-1][t']
    for (int t = 1; t <= 200; t++) {
      if (a == -1 || a == t) // Only assign if valid
        g[i][t] = s2;
      add(s2, f[i - 1][t]);
      add(s2, g[i - 1][t]);
    }
  }
  int ans = 0;
  for (int t = 1; t <= 200; t++) {
    add(ans, f[n][t]); // Sum up all valid final states
  }
  printf("%d\n", ans);
}


// https://github.com/VaHiX/codeForces/