// Problem: CF 962 D - Merge Equals
// https://codeforces.com/contest/962/problem/D

/*
Algorithm/Technique: Simulation with Map and Array Tracking
The algorithm simulates the merging process of equal elements in an array.
It uses a map to keep track of the last seen index of each value, and an array to mark 
which positions have been merged. For each new element, if it has been seen before,
we merge it with the previous occurrence and continue merging upward until no more 
merges are possible.

Time Complexity: O(n log n) - Each element can be processed in logarithmic time due to map operations.
Space Complexity: O(n) - Storage for the map, the array, and auxiliary arrays.
*/

#include <stdio.h>
#include <map>

using namespace std;
typedef long long ll;
map<ll, int> mp;  // Map to store the last index where a value was seen
ll a[1000010], vis[1000001];  // Array to store values and visited flags
int main(int argc, char const *argv[]) {
  int n, cnt = 0;  // cnt tracks number of elements that get merged out

  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    // While the current value has been seen before (in the map)
    while (mp[a[i]]) {
      int pre = mp[a[i]];  // Get index of previous occurrence
      mp[a[i]] = 0;        // Mark the previous index as free
      vis[pre] = 1;        // Mark the previous index as merged
      cnt--;               // Decrease count of active elements
      a[i] = a[i] << 1;    // Double the current value (merge)
    }
    mp[a[i]] = i;  // Store the current index of this value
  }

  printf("%d\n", n + cnt);  // Print final number of elements
  for (int i = 1; i <= n; i++)
    if (vis[i] == 0)  // Print only non-merged elements
      printf("%lld ", a[i]);
  return 0;
}


// https://github.com/VaHiX/CodeForces/