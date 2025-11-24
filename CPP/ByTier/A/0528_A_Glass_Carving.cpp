// Problem: CF 528 A - Glass Carving
// https://codeforces.com/contest/528/problem/A

/*
Code Purpose:
This code simulates the process of cutting a rectangular glass sheet into smaller fragments using a series of horizontal and vertical cuts.
After each cut, it determines the maximum area of the resulting rectangular fragments.

Algorithms/Techniques:
- Use of multiset and set data structures to efficiently manage and query the sizes of horizontal and vertical segments.
- For each cut, update the segment sets and calculate the new maximum area.

Time Complexity: O(n log n)
Space Complexity: O(n)

*/
#include <stdio.h>
#include <set>

using namespace std;
multiset<int> sh, sv;   // sh: multiset of horizontal segment lengths, sv: multiset of vertical segment lengths
set<int> hz, vt;       // hz: set of horizontal cut positions, vt: set of vertical cut positions
set<int>::iterator it1, it2;  // iterators for position sets
multiset<int>::iterator itm;  // iterator for segment length sets
int main() {
  int w, h, n;
  scanf("%d %d %d", &w, &h, &n);
  hz.insert(0);            // Insert initial lower edge
  hz.insert(h);            // Insert initial upper edge
  sh.insert(h);            // Insert full height as one segment
  vt.insert(0);            // Insert initial left edge
  vt.insert(w);            // Insert initial right edge
  sv.insert(w);            // Insert full width as one segment
  
  for (int i = 0; i < n; i++) {
    char c;
    int a;
    scanf(" %c %d", &c, &a);
    long long int mxv, mxh;
    if (c == 'H') {          // Handle horizontal cut
      mxv = (*(--sv.end())); // Get current max vertical segment
      it1 = hz.lower_bound(a); // Find next horizontal cut position
      it2 = it1;
      it2--;                    // Get previous cut position
      int b = (*it1) - (*it2);  // Original segment length
      int d1 = (*it1) - a;      // New segment 1 length
      int d2 = a - (*it2);      // New segment 2 length
      itm = sh.lower_bound(b);  // Find original segment in multiset
      sh.erase(itm);            // Remove original segment
      hz.insert(a);             // Add new cut position
      sh.insert(d1);            // Add new segment 1
      sh.insert(d2);            // Add new segment 2
      mxh = (*(--sh.end()));    // Get new max horizontal segment
    } else {                 // Handle vertical cut
      mxh = (*(--sh.end()));   // Get current max horizontal segment
      it1 = vt.lower_bound(a); // Find next vertical cut position
      it2 = it1;
      it2--;                    // Get previous cut position
      int b = (*it1) - (*it2);  // Original segment length
      int d1 = (*it1) - a;      // New segment 1 length
      int d2 = a - (*it2);      // New segment 2 length
      itm = sv.lower_bound(b);  // Find original segment in multiset
      sv.erase(itm);            // Remove original segment
      vt.insert(a);             // Add new cut position
      sv.insert(d1);            // Add new segment 1
      sv.insert(d2);            // Add new segment 2
      mxv = (*(--sv.end()));    // Get new max vertical segment
    }
    printf("%lld\n", mxv * mxh); // Output the maximum area after this cut
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/