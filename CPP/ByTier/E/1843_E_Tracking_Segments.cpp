// Problem: CF 1843 E - Tracking Segments
// https://codeforces.com/contest/1843/problem/E

/*
 * Problem: Tracking Segments
 * 
 * Purpose: Given an array of zeros, and a set of segments, determine the first 
 *          change (index assignment to 1) after which at least one segment becomes 
 *          "beautiful" (number of ones > number of zeros).
 * 
 * Algorithm:
 *   - Use binary search on the number of changes to find the minimum step where 
 *     at least one segment becomes beautiful.
 *   - For each candidate number of changes, calculate a prefix sum array of 
 *     the positions that have been changed to 1.
 *   - For each segment, compute the number of 1s in that segment using the 
 *     prefix sum and check if it's beautiful.
 * 
 * Time Complexity: O(q * m * log q)
 *   - Binary search: O(log q)
 *   - For each step in binary search: O(q + m)
 *   - Total: O(q * m * log q)
 * 
 * Space Complexity: O(n)
 *   - To store the prefix sum array and other temporary data structures.
 */

#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

#define db(...)
#ifdef WozMit
#include <wozmit>
#endif
using namespace std;

int main() {
#ifdef WozMit
  clock_t _start = clock();
#endif
  int te;
  scanf("%d", &te);
  vector<pair<int, int>> intervals;
  vector<int> changes, pref;
  
  while (te--) {
    int n, m;
    scanf("%d %d", &n, &m);
    db(n, m, "______________________");
    intervals.resize(m);
    
    // Read segments and convert to 0-based indexing
    for (auto &[x, y] : intervals) {
      scanf("%d %d", &x, &y);
      x--;
      y--;
    }
    db(intervals);
    
    int q;
    scanf("%d", &q);
    changes.resize(q);
    
    // Read changes and convert to 0-based indexing
    for (int i = 0; i < q; ++i) {
      scanf("%d", &changes[i]);
      changes[i]--;
    }
    
    // Binary search for the minimum change number
    int l = -1, r = q;
    while (r - l > 1) {
      int m = (l + r) / 2;
      
      // Initialize prefix sum array
      pref.assign(n, 0);
      
      // Mark all changes up to current midpoint
      for (int i = 0; i <= m; ++i)
        pref[changes[i]] = 1;
      
      // Calculate prefix sums
      for (int i = 1; i < n; ++i)
        pref[i] += pref[i - 1];
      
      bool possible = false;
      
      // Check each segment for beauty
      for (auto &[x, y] : intervals) {
        int nones = pref[y] - (x - 1 >= 0 ? pref[x - 1] : 0);
        int seglen = y - x + 1;
        if (nones > seglen - nones) {
          possible = true;
          break;
        }
      }
      
      if (possible)
        r = m;  // Try to find a smaller valid index
      else
        l = m;  // Need more changes to make at least one beautiful
    }
    
    db(l + 1, r + 1);
    
    // Output result
    if (r < q)
      printf("%d\n", r + 1);
    else
      puts("-1");
  }
#ifdef WozMit
  printf("%30c Executed in %.3f s.\n", 32,
         (double)(clock() - _start) / CLOCKS_PER_SEC);
#endif
  return 0;
}


// https://github.com/VaHiX/CodeForces/