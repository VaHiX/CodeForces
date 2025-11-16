// Problem: CF 733 D - Kostya the Sculptor
// https://codeforces.com/contest/733/problem/D

/*
 * Problem: Kostya the Sculptor
 * 
 * Purpose: Given n rectangular parallelepipeds (3D boxes), select at most 2 boxes 
 *          to form the largest possible inscribed sphere in a resulting shape.
 *          If 2 boxes are selected, they can be glued together along a face.
 *          
 * Approach:
 *   1. Normalize all boxes by sorting their dimensions (x <= y <= z).
 *   2. For each box, store the smallest dimension as potential maximum radius.
 *   3. Sort boxes using normalized dimensions.
 *   4. Check adjacent boxes in sorted order for possible gluing:
 *      - Two boxes can be glued if they share two equal dimensions after rotation.
 *      - When glued, new dimensions are [x1+x2, y, z] where y and z match.
 *   5. Compute resulting sphere radius for glued pairs: min(x1+x2, y, z) / 2.
 *   6. Select the best single or pair of boxes.
 * 
 * Time Complexity: O(n log n) due to sorting.
 * Space Complexity: O(n) for storing box data.
 * 
 * Algorithms/Techniques: 
 *   - Sorting with custom comparator
 *   - Greedy approach to find max inscribed sphere
 *   - Geometry: Inscribed sphere radius = min(dim1, dim2, dim3) / 2
 *   - Box normalization via dimension sorting
 */

#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 100003;
struct node {
  int x, y, z, id;
} b[maxn];
int n;
int a[3];
bool cmp(node a, node b) {
  if (a.z != b.z)
    return a.z < b.z;
  if (a.y != b.y)
    return a.y < b.y;
  return a.x < b.x;
}
int main() {
  int ans = 0, id = 0, id1 = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d%d", &a[0], &a[1], &a[2]);
    sort(a, a + 3);           // Normalize box dimensions: x <= y <= z
    b[i].x = a[0], b[i].y = a[1], b[i].z = a[2];
    if (a[0] > ans) {         // Keep track of best single box
      ans = a[0];
      id = i;
    }
    b[i].id = i;
  }
  sort(b + 1, b + n + 1, cmp);  // Sort normalized boxes
  for (int i = 2; i <= n; ++i)
    if (b[i].z == b[i - 1].z && b[i].y == b[i - 1].y) {
      // If two boxes can be glued together on face defined by y and z
      if (min(b[i].x + b[i - 1].x, min(b[i].y, b[i - 1].y)) > ans) {
        // Calculate radius of inscribed sphere from glued box
        ans = min(b[i].x + b[i - 1].x, min(b[i].y, b[i - 1].y));
        id = b[i].id;
        id1 = b[i - 1].id;
      }
    }
  if (id1)
    printf("2\n%d %d\n", id, id1);  // Output two boxes
  else
    printf("1\n%d\n", id);         // Output one box
  return 0;
}


// https://github.com/VaHiX/CodeForces/