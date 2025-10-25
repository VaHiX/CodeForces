// Problem: CF 1641 A - Great Sequence
// https://codeforces.com/contest/1641/problem/A

/*
 * Problem: A. Great Sequence
 * Purpose: Given a sequence of positive integers and a multiplier x,
 *          determine the minimum number of elements to add so that
 *          the sequence can be split into pairs where one element is x times the other.
 *
 * Algorithms/Techniques:
 *   - Greedy approach with multiset for efficient lookup and removal.
 *   - Sorting the array to process elements in ascending order.
 *   - For each element, try to pair it with an existing element that is its divisor by x.
 *     If such a pair can be formed, remove both from the set. Otherwise, insert the current
 *     element into the multiset.
 *
 * Time Complexity: O(n log n) per test case due to sorting and multiset operations.
 * Space Complexity: O(n) for storing elements in the multiset.
 */

#include <stdio.h>
#include <algorithm>
#include <set>

using namespace std;
int n, x, a[1000005];
multiset<int> mp;

int main() {
  int i, T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &x), mp.clear(); // Read input and clear multiset
    for (i = 1; i <= n; ++i) {
      scanf("%d", a + i); // Read array elements
    }
    sort(a + 1, a + n + 1); // Sort the array to process in order
    
    // Iterate through sorted array and try to form pairs
    for (i = 1; i <= n; ++i)
      if (a[i] % x == 0 && mp.find(a[i] / x) != mp.end()) // If current element has a matching pair
        mp.erase(mp.find(a[i] / x)); // Remove the paired element
      else
        mp.insert(a[i]); // Otherwise insert current element into multiset
    
    printf("%d\n", int(mp.size())); // Output number of unpaired elements (i.e., additions needed)
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/