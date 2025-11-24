// Problem: CF 1765 D - Watch the Videos
// https://codeforces.com/contest/1765/problem/D

/*
Purpose: This code solves the problem of determining the minimum time required to watch all videos,
         given constraints on disk space and download times.

Algorithms/Techniques: 
    - Two-pointer technique after sorting the array of video sizes.
    - Greedy approach to pair videos such that their combined size does not exceed disk capacity.

Time Complexity: O(n log n), due to sorting the array of video sizes.
Space Complexity: O(1), as we only use a constant amount of extra space (excluding input storage).

*/

#include <stdio.h>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
  int k, n;
  scanf("%d%d", &n, &k);  // Read number of videos 'n' and disk size 'k'
  int a[n], l = 0, r = n - 1;  // Two pointers: l for left, r for right
  ll res = 1;  // Initialize result with 1 minute for watching the first video
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]), res += a[i];  // Read video sizes and accumulate total download time
  sort(a, a + n);  // Sort the array to enable two-pointer technique
  while (l < r) {
    if (a[l] + a[r] <= k)  // If the smallest and largest unprocessed videos fit together
      l++, r--;  // Move both pointers inward
    else
      r--, res++;  // Otherwise, reduce the larger video's size and increment result (extra minute needed)
  }
  printf("%lld", res);  // Output the minimum time required
}


// https://github.com/VaHiX/CodeForces/