// Problem: CF 1873 D - 1D Eraser
// https://codeforces.com/contest/1873/problem/D

using System;
using System.Linq;
using System.Collections.Generic;
class sol {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      string[] str = Console.ReadLine().Split(' ');
      int ans = 0;
      int n = int.Parse(str[1]); // Length of the strip
      string s = Console.ReadLine();
      for (int i = 0; i < s.Length; i++) {
        if (s[i] == 'B') { // If we encounter a black cell
          i += n - 1; // Skip the next (n-1) cells as they will be covered by one operation
          ans++; // Increment the operation count
        }
      }
      Console.WriteLine(ans);
    }
  }
}
/*
Algorithm: Greedy Approach
Time Complexity: O(n) for each test case, where n is the length of the string.
Space Complexity: O(1) excluding the input storage.

This solution uses a greedy approach:
1. Traverse the string from left to right.
2. When a 'B' is encountered, perform an operation starting at that position.
3. This operation will cover the next k-1 cells, ensuring all black cells in this range are eliminated.
4. The index is incremented by (k-1) to skip already covered cells.

The greedy approach works because:
- Each time we perform an operation, we ensure the leftmost black cell is removed.
- There's no benefit in starting an operation at a later position when an earlier one would suffice.
Thus, the number of operations is minimized.
*/

// https://github.com/VaHiX/CodeForces/