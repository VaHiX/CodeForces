// Problem: CF 1712 D - Empty Graph
// https://codeforces.com/contest/1712/problem/D

/*
Purpose: Solve the problem of maximizing the diameter of a graph built from an array
         after performing at most k operations to modify array values.

Algorithms/Techniques:
- Binary search on the answer (on the possible diameter value)
- Greedy approach to determine the minimum number of operations needed
  to ensure a certain diameter can be achieved
- Preprocessing the array to mark which elements are too small to achieve a target
  diameter, and then determining how many edits are needed to fix the gaps

Time Complexity: O(n * log(1e9)) where n is the size of array, log(1e9) due to binary search
Space Complexity: O(n) for the auxiliary array b[] used in computation
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int a[N], b[N];

void solve() {
  int n, k, ans = 0, tr = 0;
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  
  int l = 1, r = 1e9;  // Binary search bounds for possible diameter values
  while (l <= r) {
    int mid = (l + r) / 2, cnt = 0;
    
    // Mark elements that are too small to contribute to a path of weight 'mid'
    for (int i = 1; i <= n; i++) {
      if (a[i] * 2 < mid) {  // If element is less than mid/2, it cannot form a path of weight mid
        cnt++;  // Count how many such elements there are
        b[i] = 1e9;  // Mark them as unavailable
      } else {
        b[i] = a[i];  // Keep original value for possible use
      }
    }
    
    // Determine minimum number of operations to make a valid path of weight 'mid'
    int mi = 2;  // Start with 2, since we need at least 2 nodes to form an edge
    for (int i = 1; i < n; i++)
      mi = min(mi, 0 + (b[i] < mid) + (b[i + 1] < mid));
    
    // If total operations (count of bad elements + minimum operations needed) is <= k
    if (cnt + mi <= k)
      l = mid + 1;  // Try a larger diameter
    else
      r = mid - 1;  // Try a smaller diameter
  }
  printf("%d\n", r);  // The largest valid diameter
}

int main(void) {
  int t = 1;
  scanf("%d", &t);
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/