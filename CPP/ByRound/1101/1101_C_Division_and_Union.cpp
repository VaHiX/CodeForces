// Problem: CF 1101 C - Division and Union
// https://codeforces.com/contest/1101/problem/C

/*
Algorithm: 
- This is a graph bipartitioning problem on interval segments.
- We need to partition the intervals into two groups such that no two intervals from different groups intersect.
- The approach is to sort the intervals by their left endpoint.
- Then, we iterate through these sorted intervals and assign them to groups greedily.
- For each interval, if it doesn't intersect with the last interval in the current group, we put it in the same group.
- Otherwise, we switch to the other group.
- If at any point, all intervals end up in the same group, it's impossible to partition into two non-empty groups.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the intervals and their assignments

Techniques:
- Sorting by left endpoint
- Greedy assignment to groups
- Bit manipulation to store index along with left endpoint
*/

#include <algorithm>
#include <cstdio>

using namespace std;

long long l, a[100000];
int i, j, t, n, m, g, b[100000], s[100000];

int main() {
  for (scanf("%d", &t); t--;) {
    scanf("%d", &n);
    for (i = j = m = g = 0; i < n; i++) {
      scanf("%lld%d", &l, b + i);
      a[i] = l << 32 | i;  // Store left endpoint in higher 32 bits, index in lower 32 bits
    }
    std::sort(a, a + n);  // Sort by left endpoint
    
    for (; j < n; j++) {
      i = a[j];  // Get original index
      g += a[j] >> 32 > m;  // Increment group counter if current left > last right (no overlap)
      m = b[i] > m ? b[i] : m;  // Update max right endpoint
      s[i] = 2 - g % 2;  // Assign to group 1 or 2 based on parity of group counter
    }
    
    if (g < 2) {  // If we have less than 2 groups, impossible to partition
      n = 1;
      *s = -1;
    }
    
    for (i = 0; i < n; i++)
      printf("%d ", s[i]);  // Print group assignments
  }
}


// https://github.com/VaHiX/CodeForces/