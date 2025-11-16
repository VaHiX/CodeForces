// Problem: CF 1772 B - Matrix Rotation
// https://codeforces.com/contest/1772/problem/B

using System;
class prog {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      // Read the first row of the matrix
      string[] s = Console.ReadLine().Split(' ');
      int a = int.Parse(s[0]);
      int b = int.Parse(s[1]);
      // Read the second row of the matrix
      s = Console.ReadLine().Split(' ');
      int c = int.Parse(s[0]);
      int d = int.Parse(s[1]);
      
      bool ok = false; // Flag to check if matrix can be made beautiful
      
      // Check the original matrix
      if (a < b && b < d && a < c && c < d)
        ok = true;
      
      // Rotate the matrix 90 degrees clockwise and check
      int x = b, y = c, z = d;
      b = a;
      d = x;
      a = y;
      c = z;
      if (!ok && a < b && b < d && a < c && c < d)
        ok = true;
      
      // Rotate again
      x = b;
      y = c;
      z = d;
      b = a;
      d = x;
      a = y;
      c = z;
      if (!ok && a < b && b < d && a < c && c < d)
        ok = true;
      
      // Rotate again
      x = b;
      y = c;
      z = d;
      b = a;
      d = x;
      a = y;
      c = z;
      if (!ok && a < b && b < d && a < c && c < d)
        ok = true;
      
      // Rotate one more time to complete full 360 degree rotation
      x = b;
      y = c;
      z = d;
      b = a;
      d = x;
      a = y;
      c = z;
      if (!ok && a < b && b < d && a < c && c < d)
        ok = true;
      
      Console.WriteLine(ok ? "YES" : "NO");
    }
  }
}
/*
Algorithm: Brute Force with Rotation
Approach:
- For a 2x2 matrix, we can try all possible rotations (0°, 90°, 180°, 270°).
- For each rotation, we check if the matrix satisfies the beauty condition:
  - Each row has first element smaller than second element.
  - Each column has first element smaller than second element.
- Time Complexity: O(1) - Since there are only 4 rotations to check, and each check takes constant time.
- Space Complexity: O(1) - Only storing a few variables, no extra space used.
*/

// https://github.com/VaHiX/CodeForces/