// Problem: CF 1419 D1 - Sage's Birthday (easy version)
// https://codeforces.com/contest/1419/problem/D1

/*
Algorithm/Technique: 
- The problem requires arranging ice spheres such that the maximum number of "cheap" spheres are formed.
- A sphere is cheap if it is less than both its neighbors.
- The strategy is to sort the array in descending order, then interleave elements to create a pattern where peaks and valleys form to maximize cheap elements.
- Time Complexity: O(n log n) due to sorting.
- Space Complexity: O(n) for storing the input and output arrays.

Approach:
- Sort the array in descending order.
- Distribute the elements into two groups: one group goes to even indices, another to odd indices.
- If n is even, the smallest element is placed at the end.
- Then print the resulting arrangement.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  sort(a.rbegin(), a.rend()); // Sort in descending order
  long last(-1);
  if (n % 2 == 0) {
    last = a.back(); // Save the smallest element for later
    a.pop_back();    // Remove it from the list
  }
  std::vector<long> b(a.size());
  long idx(0);
  for (long p = 0; p < n; p += 2) {
    b[p] = a[idx++]; // Assign to even positions
  }
  for (long p = 1; p < n; p += 2) {
    b[p] = a[idx++]; // Assign to odd positions
  }
  if (last > 0) {
    b.push_back(last); // Place the saved element at the end if needed
  }
  printf("%ld\n", (n - 1) / 2); // Maximum number of cheap items
  for (long p = 0; p < b.size(); p++) {
    printf("%ld ", b[p]); // Print the final arrangement
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/