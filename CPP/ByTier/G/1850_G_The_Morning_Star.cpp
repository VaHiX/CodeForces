// Problem: CF 1850 G - The Morning Star
// https://codeforces.com/contest/1850/problem/G

/*
Purpose: 
This code solves the problem of counting valid pairs of points (compass and morning star) such that the compass direction between them is valid (one of the 8 allowed directions: N, S, E, W, NE, NW, SE, SW). 

The solution leverages the fact that valid compass directions are determined by the relative differences in x and y coordinates. For each of the four combinations:
- x difference (dx)
- y difference (dy)
- x + y difference (dx + dy)
- x - y difference (dx - dy)

We count how many points share the same value in each of these difference sets, and compute the number of pairs (combinations) of points for each set. For n points with the same difference, the number of valid pairs is n * (n - 1).

Algorithms:
- The core algorithm uses sorting and grouping to count occurrences of the same values in four key difference types.
- For each group of same difference values, we calculate combinations using the formula: cnt * (cnt - 1).

Time Complexity: O(n log n) per test case due to sorting steps.
Space Complexity: O(n) for storing coordinates and auxiliary arrays.

*/
#include <algorithm>
#include <stdio.h>
using std::sort;
typedef long long ll;
const int MAXN = 200005;
int x[MAXN], y[MAXN], p[MAXN], n, prev;
ll ans, cnt;

// Count the number of valid pairs by grouping same values in array p
void count() {
  sort(p + 1, p + n + 1); // Sort the array to group same elements together
  prev = p[1], cnt = 1;
  for (int i = 2; i <= n; ++i) {
    if (p[i] == prev) { // If current element is same as previous
      ++cnt;           // Increase count
    } else {
      ans += cnt * (cnt - 1); // Add combinations for previous group
      cnt = 1;                // Reset count
    }
    prev = p[i];   // Update previous element
  }
  ans += cnt * (cnt - 1); // Add combinations for the last group
}

// Main function to process each test case
void solve() {
  ans = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d%d", x + i, y + i);
  
  // Check all 4 difference types
  for (int i = 1; i <= n; ++i)
    p[i] = x[i];            // dx
  count();
  
  for (int i = 1; i <= n; ++i)
    p[i] = y[i];            // dy
  count();
  
  for (int i = 1; i <= n; ++i)
    p[i] = x[i] + y[i];     // dx + dy
  count();
  
  for (int i = 1; i <= n; ++i)
    p[i] = x[i] - y[i];     // dx - dy
  count();
  
  printf("%lld\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/