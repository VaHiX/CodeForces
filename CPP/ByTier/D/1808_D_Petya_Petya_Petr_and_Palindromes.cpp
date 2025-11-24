// Problem: CF 1808 D - Petya, Petya, Petr, and Palindromes
// https://codeforces.com/contest/1808/problem/D

/*
 * Problem: Petya, Petya, Petr, and Palindromes
 * 
 * Purpose: Given a sequence of integers and an odd integer k, compute the sum of palindromicity
 *          for all subarrays of length k. Palindromicity is the minimum number of elements that
 *          need to be changed to make a subarray a palindrome.
 * 
 * Algorithm: 
 *  - For each subarray of length k, we determine how many pairs of elements need to be made equal
 *    to form a palindrome (considering symmetric positions).
 *  - Use a sweep line approach with events to efficiently calculate the number of matching pairs
 *    as we slide through the array.
 *  - Time complexity: O(n log n) due to sorting events.
 *  - Space complexity: O(n) for storing events and auxiliary arrays.
 * 
 * Techniques:
 *  - Two-pointers / sliding window
 *  - Coordinate compression via event processing
 *  - Sorting events based on positions
 * 
 */

#include <algorithm>
#include <stdio.h>
typedef long long ll;

struct node {
  int x, y, z; // x: event position, y: element value, z: +1 for start, -1 for end
};

int n, k, m;
int a[200005]; // input array
node b[400005]; // event array
int cnt[2][200005]; // count array for even/odd indices
ll ans;

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  
  // Initialize answer with the total number of pairs that need to be checked
  ans = (ll)(n - k + 1) * ((k - 1) / 2);
  
  // For each element in the array, determine the range of subarrays where 
  // this element affects the palindromicity
  for (int i = 1, l, r; i <= n; i++) {
    l = std::max(i + 1, (k + 1) / 2); // Left bound of the valid subarray region
    r = std::min(i + (k - 1) / 2, n - (k - 1) / 2); // Right bound of the valid subarray region
    
    if (l <= r) {
      // Add start and end events to the event list (using transformed positions)
      b[++m] = node{l + l - i - 2, a[i], 1};   // Start of interval
      b[++m] = node{r + r - i, a[i], -1};      // End of interval
    }
  }
  
  // Sort all events by their positions (x coordinate)
  std::sort(b + 1, b + m + 1, [](node x, node y) { return x.x < y.x; });
  
  // Sweep through positions to process events
  for (int i = 1, j = 1; i <= n; i++) {
    // Increment count for current element at index i
    ++cnt[i & 1][a[i]];
    
    // Process all events at current position i
    while (j <= m && b[j].x == i) {
      ans += cnt[i & 1][b[j].y] * b[j].z;
      ++j;
    }
  }
  
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/