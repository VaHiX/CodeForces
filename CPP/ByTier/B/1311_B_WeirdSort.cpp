// Problem: CF 1311 B - WeirdSort
// https://codeforces.com/contest/1311/problem/B

/*
B. WeirdSort
Algorithm: Union-Find / Connected Components
Time Complexity: O(n^2 * log n) per test case due to sorting and set operations.
Space Complexity: O(n) for storing the array and set.

The problem involves determining whether an array can be sorted using only allowed adjacent swaps.
We model this by grouping indices that are connected via allowed positions (i.e., if we can swap a[i] with a[i+1],
and a[i+1] with a[i+2], then all elements in between can "move" together). We use Union-Find or similar logic to
determine which indices form connected components. Then for each component, we sort the values and check if
the final array is sorted.
*/

#include <stdio.h>
#include <algorithm>
#include <set>

int i, j, k, n, m, a[100];
int main() {
  for (scanf("%*d"); ~scanf("%d%d", &n, &m); i = j = 0) {        // Read number of test cases, initialize variables
    std::set<int> p;                                            // Store allowed positions in a set
    for (; i < n; i++)
      scanf("%d", a + i);                                       // Read the array elements
    while (m--)
      scanf("%d", &i), p.insert(i);                             // Read and insert allowed adjacent swaps into the set
    for (k = 1; k <= n; k++)                                    // Iterate over possible segments
      if (!p.count(k))                                          // If current index is not in allowed positions
        std::sort(a + j, a + k), j = k;                         // Sort segment from j to k and update j
    puts(std::is_sorted(a, a + n) ? "YES" : "NO");              // Check if the whole array is sorted
  }
}


// https://github.com/VaHiX/codeForces/