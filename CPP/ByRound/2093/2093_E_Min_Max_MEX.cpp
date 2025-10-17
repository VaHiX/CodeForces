// Problem: CF 2093 E - Min Max MEX
// https://codeforces.com/contest/2093/problem/E

/*
E. Min Max MEX
Algorithms/Techniques: Binary Search + Greedy + Sliding Window Concept
Time Complexity: O(n * log n) per test case
Space Complexity: O(n)

The problem asks to split an array into k non-overlapping subarrays such that 
the minimum MEX among all subarrays is maximized. We use binary search on the 
answer (MEX value), and for each candidate MEX value, we check whether it's possible 
to partition the array into k subarrays where each has MEX at least the candidate value.

The helper function 'check' uses a greedy approach to simulate the splitting process:
- For a given mid (candidate MEX), it checks if we can split the array into k segments,
  such that each segment has MEX >= mid.
- It keeps track of last occurrence of elements and ensures no element repeats 
  within a subarray beyond what's allowed for MEX = mid.

*/
#include <stdio.h>
#include <iosfwd>

using namespace std;
int T, n, k, a[200005], t[200005];
bool check(int mid) {
  int cnt = 0, ans = 0;
  for (int i = 0; i <= mid; i++)
    t[i] = 0; // Reset the tracking array for each mid value
  for (int i = 1; i <= n; i++) {
    if (a[i] < mid && t[a[i]] <= ans) { // If element is valid and hasn't been used
      cnt++;                           // Count how many different elements we've added
      t[a[i]] = ans + 1;               // Mark that this value was used in this group
    }
    if (cnt == mid) {                  // When we have filled up to mid distinct values
      cnt = 0;                         // Reset counter for next group
      ans++;                           // Start new group
    }
  }
  return ans >= k; // If we can form at least k groups, this mid is achievable
}
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]);
    int l = 0, r = n + 1;
    while (l < r) {
      int mid = (l + r + 1) / 2;       // Binary search on answer
      if (check(mid))
        l = mid;
      else
        r = mid - 1;
    }
    printf("%d\n", l);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/