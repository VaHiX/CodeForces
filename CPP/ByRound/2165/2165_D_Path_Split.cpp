// Problem: CF 2165 D - Path Split
// https://codeforces.com/contest/2165/problem/D

/*
Algorithm: Greedy + Set
The problem is to partition a sequence into minimum number of subsequences such that each subsequence forms a path in a graph where edges exist between consecutive integers (|a[i] - a[j]| = 1).

Approach:
1. For each value in the array, we keep track of its indices.
2. We iterate from the maximum possible value down to 1.
3. For each value o, we look at all indices where o appears.
4. At each index pos where o appears:
   - We check if there's a previous element (o-1) or next element (o+1) that can form a consecutive path.
   - If we can form a path with either of them, we reduce the answer count (as we're merging two paths).
5. Using sets to efficiently find and erase elements in O(log n) time.

Time Complexity: O(n log n) per test case due to set operations and iteration over elements.
Space Complexity: O(n) for storing indices and sets.

*/
#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>

using namespace std;
#define _int64 long long
#define mo 998244353
int a[1100000];
vector<int> ind[2100000]; // Store indices for each value
set<int> st[2100000];     // Store indices in a set for efficient lookup
int main() {
  int i, j, k, n, l, t, m, x, y, o, b1, pos, ans;
  scanf("%d", &t);
  for (l = 0; l < t; l++) {
    scanf("%d", &n);
    for (i = 0; i < n; i++)
      scanf("%d", &a[i]);
    for (i = 0; i <= n + n + 1; i++) {
      ind[i].clear();   // Clear all index vectors
      st[i].clear();    // Clear all sets
    }
    for (i = 0; i < n; i++) {
      ind[a[i]].push_back(i);   // Store index of each element
      st[a[i]].insert(i);       // Insert index into set for value a[i]
    }
    ans = n;  // Initially assume each element is in its own subsequence
    for (o = n + n; o > 0; o--) {
      for (i = 0; i < ind[o].size(); i++) {
        pos = ind[o][i]; // Current position in array
        set<int>::iterator it = st[o + 1].lower_bound(pos); // Find nearest element with value o+1
        if (it != st[o + 1].begin()) { // If there's an element before it
          it--; // Move to the previous element
          st[o + 1].erase(*it); // Remove the previous element (we're connecting paths)
          ans--; // Decrease count of subsequences
          continue;
        }
        it = st[o - 1].lower_bound(pos); // Find nearest element with value o-1
        if (it != st[o - 1].begin()) { // If there's an element before it
          it--; // Move to the previous element
          st[o - 1].erase(*it); // Remove the previous element (we're connecting paths)
          ans--; // Decrease count of subsequences
          continue;
        }
      }
    }
    printf("%d\n", ans);
  }
}


// https://github.com/VaHiX/CodeForces/