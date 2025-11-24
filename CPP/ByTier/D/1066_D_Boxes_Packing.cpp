// Problem: CF 1066 D - Boxes Packing
// https://codeforces.com/contest/1066/problem/D

/*
D. Boxes Packing
Algorithm: Greedy with sliding window approach
Time Complexity: O(n)
Space Complexity: O(1)

Maksim wants to pack n objects into m boxes of size k each using a greedy algorithm:
- He takes the first available box and fills it with objects from left to right until 
  no more objects fit in that box. Then he moves to the next empty box.
- If all m boxes are filled but some objects remain, he cannot pack them.
- To maximize number of packed objects, we try different starting positions 
  (throwing out leftmost objects) and find the maximum valid count.

The solution uses a reverse iteration approach:
1. Start from the last object and go backwards
2. Track current box weight (w) and number of boxes used (number)
3. When we can't fit an object in the current box and have remaining boxes,
   start a new box
4. When no more boxes are left and we can't pack current object, stop
5. Return how many objects from the end were successfully packed

*/
#include <stdio.h>
#define max 200000
int main() {
  int n, m, k, i, w, number;
  int a[max];
  scanf("%d%d%d", &n, &m, &k);
  for (i = 0; i < n; i++)
    scanf("%d", a + i);
  for (i = n - 1, w = 0, number = 0; i >= 0; i--) {
    w += a[i]; // Add current object to the box
    if (w > k && number < m - 1) { // If object doesn't fit and we have boxes left
      w = 0; // Reset box weight
      w += a[i]; // Start new box with current object
      number++; // Increment box count
    }
    if (w > k && number == m - 1) // If no more boxes and can't fit
      break;
  }
  printf("%d\n", n - 1 - i); // Print number of objects packed
  return 0;
}


// https://github.com/VaHiX/codeForces/