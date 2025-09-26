// Problem: CF 2113 B - Good Start
// https://codeforces.com/contest/2113/problem/B

/*
 * Problem: B. Good Start
 * Purpose: Determine whether a roof of size w x h can be completely tiled with a x b sheets,
 *          given that two sheets are already placed at positions (x1, y1) and (x2, y2).
 *
 * Algorithms/Techniques:
 *   - Modular arithmetic to determine tile alignment
 *   - Check three conditions for valid tiling:
 *     1. Vertical alignment: same x-offset but different x-coordinates (vertical line)
 *     2. Horizontal alignment: same y-offset but different y-coordinates (horizontal line)
 *     3. Grid alignment: same offsets in both directions (complete grid pattern)
 *
 * Time Complexity: O(1) - constant time due to fixed number of operations
 * Space Complexity: O(1) - constant space used
 */

using System;
class Program {
  static bool CanTileRoof(long w, long h, long a, long b, long x1, long y1,
                          long x2, long y2) {
    // Calculate remainders when placing sheets
    long rx1 = x1 % a;     // x remainder for first sheet
    long rx2 = x2 % a;     // x remainder for second sheet  
    long ry1 = y1 % b;     // y remainder for first sheet
    long ry2 = y2 % b;     // y remainder for second sheet

    // Handle negative remainders by adding tile size
    if (rx1 < 0)
      rx1 += a;
    if (rx2 < 0)
      rx2 += a;
    if (ry1 < 0)
      ry1 += b;
    if (ry2 < 0)
      ry2 += b;

    // Check if the two sheets are aligned vertically (same x_offset, different x_positions)
    bool verticalOk = (rx1 == rx2 && x1 != x2);

    // Check if the two sheets are aligned horizontally (same y_offset, different y_positions)
    bool horizontalOk = (ry1 == ry2 && y1 != y2);

    // Check if the two sheets form a complete grid pattern (same offsets in both directions)
    bool gridOk = (rx1 == rx2 && ry1 == ry2);

    // Return true if any of the three alignment patterns allows full tiling
    return verticalOk || horizontalOk || gridOk;
  }
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    for (int i = 0; i < t; i++) {
      var whab = Array.ConvertAll(Console.ReadLine().Split(), long.Parse);
      var coords = Array.ConvertAll(Console.ReadLine().Split(), long.Parse);
      bool result = CanTileRoof(whab[0], whab[1], whab[2], whab[3], coords[0],
                                coords[1], coords[2], coords[3]);
      Console.WriteLine(result ? "Yes" : "No");
    }
  }
}


// https://github.com/VaHiX/codeForces/