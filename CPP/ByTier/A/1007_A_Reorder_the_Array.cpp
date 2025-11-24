// Problem: CF 1007 A - Reorder the Array
// https://codeforces.com/contest/1007/problem/A

/*
Problem: Maximize the number of elements that become larger after permuting the array.
Algorithm: Two-pointer technique after sorting.
Time Complexity: O(n log n) due to sorting; two-pointer traversal is O(n).
Space Complexity: O(1) excluding input storage.

The idea is to sort the array and use two pointers:
- One pointer (`left`) tracks the smallest elements that can be replaced.
- Another pointer (`right`) scans through the sorted array.
We count how many times we can place a larger element in a position where a smaller one was.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll n;
  scanf("%lld", &n);
  std::vector<ll> a(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
  }
  sort(a.begin(), a.end()); // Sort the array to apply two-pointer technique
  ll left(0), right(0), cnt(0);
  while (right < n && a[left] == a[right]) {
    ++right; // Skip duplicates from the start
  }
  while (right < n) {
    if (a[left] < a[right]) { // If current element is larger than the one we are trying to replace
      ++cnt; // Increment count of positions where element increased
      ++left; // Move left pointer to next element
    }
    ++right; // Always move right pointer forward
  }
  printf("%lld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/codeForces/