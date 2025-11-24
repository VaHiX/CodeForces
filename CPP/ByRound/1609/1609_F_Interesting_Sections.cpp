// Problem: CF 1609 F - Interesting Sections
// https://codeforces.com/contest/1609/problem/F

/*
 * Problem: F. Interesting Sections
 * 
 * Algorithm: Divide and Conquer with Two Pointers and Bit Counting
 * 
 * Approach:
 * - Use a recursive divide-and-conquer strategy to split the array into halves.
 * - For each segment, we compute the minimum value from left to right and use two pointers 
 *   to efficiently count valid segments where min and max have the same number of set bits.
 * - The key insight is to maintain prefix min values and count how many valid segments
 *   cross the midpoint.
 * 
 * Time Complexity: O(n * log(n) * log(max(a)))
 *   - The recursion depth is O(log(n))
 *   - For each level, processing involves O(n) operations
 *   - Bit counting operations are O(60) = O(1) since max value is 1e18
 * 
 * Space Complexity: O(n + log(n))
 *   - O(n) for arrays m and t
 *   - O(log(n)) for recursion stack
 */

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>

#define int long long
using namespace std;

int n, a[1000005], ans, m[1000005], t[60];

// Return the lowest bit of x
int lowbit(int x) { return x & -x; }

// Count the number of 1s in binary representation of x
int count(int x) { return __builtin_popcountll(x); }

// Recursive function that processes subarray from l to r
void solve(int l, int r) {
  // Base case: single element segment
  if (l == r)
    return void(ans++);
  
  int mid = l + r >> 1; // Midpoint of the segment
  solve(l, mid), solve(mid + 1, r); // Recursively process left and right halves

  // Clear temporary array t
  memset(t, 0, sizeof(t));
  
  // Compute min prefix from right to left starting from mid
  m[mid] = a[mid];
  for (int i = mid - 1; i >= l; i--)
    m[i] = min(m[i + 1], a[i]);
  
  // Two-pointer approach to count segments crossing the midpoint
  for (int i = mid + 1, j = mid + 1, k = mid + 1, ma = a[mid + 1],
           mi = a[mid + 1];
       i <= r; i++) {
    ma = max(ma, a[i]);  // Update maximum value
    mi = min(mi, a[i]);  // Update minimum value
    
    // Move j to the left while maintaining condition
    while (j - 1 >= l && a[j - 1] <= ma)
      j--, t[count(m[j])]++;

    // Move k to the left while maintaining condition
    while (k - 1 >= j && mi <= m[k - 1])
      k--, t[count(m[k])]--;

    // Add valid segments that end at current i
    ans += t[count(ma)];
    
    // If min and max have same number of set bits, add additional count
    if (count(mi) == count(ma))
      ans += mid + 1 - k;
  }

  // Clear temporary array t again
  memset(t, 0, sizeof(t));
  
  // Compute min prefix from left to right starting from mid+1
  m[mid + 1] = a[mid + 1];
  for (int i = mid + 2; i <= r; i++)
    m[i] = min(m[i - 1], a[i]);
  
  // Two-pointer approach for segments crossing the midpoint from left
  for (int i = mid, j = mid, k = mid, ma = a[mid + 1], mi = a[mid + 1]; i >= l;
       i--) {
    ma = max(ma, a[i]);  // Update maximum value
    mi = min(mi, a[i]);  // Update minimum value
    
    // Move j to the right while maintaining condition
    while (j + 1 <= r && a[j + 1] < ma)
      j++, t[count(m[j])]++;

    // Move k to the right while maintaining condition
    while (k + 1 <= j && mi < m[k + 1])
      k++, t[count(m[k])]--;

    // Add valid segments that start at current i
    ans += t[count(ma)];
    
    // If min and max have same number of set bits, add additional count
    if (count(mi) == count(ma))
      ans += k - mid;
  }
}

signed main() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    scanf("%lld", &a[i]);
  solve(1, n);
  cout << ans;
  return 0;
}


// https://github.com/VaHiX/CodeForces/