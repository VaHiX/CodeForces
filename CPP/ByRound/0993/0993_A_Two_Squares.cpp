// Problem: CF 993 A - Two Squares
// https://codeforces.com/contest/993/problem/A

/*
Code Purpose:
This program determines whether two squares intersect. One square has sides parallel to the coordinate axes, and the other has sides at 45 degrees to the axes. The algorithm uses coordinate sorting and a brute-force search over the bounding rectangle of the axis-aligned square to check for intersection with the rotated square.

Algorithms/Techniques:
- Sorting coordinates to find bounding rectangles
- Brute-force point checking within the bounding box of one square
- Using the rotated square's vertices to define inequalities for intersection

Time Complexity: O(1) - Since the number of vertices is fixed (4) and the loop bounds are fixed, the time complexity is constant.
Space Complexity: O(1) - Only a fixed amount of extra space is used (arrays of size 4).
*/

#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  int x1[4], x2[4], y1[4], y2[4];
  // Read coordinates of the first square (axis-aligned)
  for (int i = 0; i < 4; i++)
    cin >> x1[i] >> y1[i];
  // Read coordinates of the second square (rotated)
  for (int i = 0; i < 4; i++)
    cin >> x2[i] >> y2[i];
  
  // Sort coordinates to find min and max for each axis
  sort(x1, x1 + 4);
  sort(y1, y1 + 4);
  sort(x2, x2 + 4);
  sort(y2, y2 + 4);
  
  // Iterate through all points in the bounding rectangle of the axis-aligned square
  for (int i = x1[0]; i <= x1[3]; i++)
    for (int j = y1[0]; j <= y1[3]; j++)
      // Check if the point (i,j) satisfies all the inequalities defining the rotated square
      if (i + j <= x2[3] + y2[2])         // Inequality for one edge
        if (i + j >= x2[0] + y2[2])       // Inequality for another edge
          if (i - j >= -y2[3] + x2[2])    // Inequality for another edge
            if (i - j <= x2[3] - y2[2]) { // Inequality for the last edge
              cout << "YES";
              return 0;
            }
  cout << "NO";
  return 0;
}


// https://github.com/VaHiX/CodeForces/