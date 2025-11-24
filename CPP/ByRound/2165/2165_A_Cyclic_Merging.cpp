// Problem: CF 2165 A - Cyclic Merging
// https://codeforces.com/contest/2165/problem/A

/*
Algorithm: Cyclic Merging
Techniques: Greedy, Ring-based merging with optimal cost calculation

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the array elements

The problem requires merging all elements in a ring into one, with each merge operation
having a cost equal to the maximum of the two merged elements. Since the merging process
is greedy and we can choose any adjacent pair, we can optimize the total cost by always
merging the smallest possible elements first. 

The key insight is that the minimal cost of merging n elements into one in a ring 
is the sum of all elements minus the maximum element. This is derived from the fact
that in any valid merging sequence, the maximum element will be merged at least once,
but it's never the cost of the final merge - it contributes to the cost of intermediate merges.

This approach works because:
1. The cost of all merges is the sum of the max of all adjacent pairs.
2. But in one optimal merge path, we don't include the maximum element in the final sum
   because it is merged into another element and contributes only to intermediate cost.
3. Since we're going through a ring, we must account for every element being adjacent
   (i.e., every element is involved in at least one merge), and by the greedy method,
   this leads to the formula: sum of all elements - maximum element.
*/
#include <stdio.h>
#include <iosfwd>

using namespace std;
const int maxn = 200100;
long long a[maxn];
long long read() {
  long long ans = 0;
  char ch = getchar();
  int f = 0;
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = 1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    ans = (ans << 1) + (ans << 3) + (ch ^ 48);
    ch = getchar();
  }
  return f ? -ans : ans;
}
int main() {
  int t = read();
  while (t--) {
    int n = read();
    for (int i = 0; i < n; ++i)
      a[i] = read();
    long long s = 0, mx = 0;
    for (int i = 0; i < n; ++i) {
      int j = i + 1 == n ? 0 : i + 1; // Handle wrap-around for ring
      long long w = a[i] > a[j] ? a[i] : a[j]; // Get max of adjacent elements
      s += w; // Sum all max adjacent pairs (total cost of merging)
      if (w > mx)
        mx = w; // Track the maximum of all such pairs
    }
    long long ans = s - mx; // Subtract the max to get optimal cost
    printf("%lld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/